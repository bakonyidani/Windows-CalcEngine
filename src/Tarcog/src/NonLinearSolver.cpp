#include <assert.h>
#include <math.h>
#include <algorithm>

#include "NonLinearSolver.hpp"
#include "WCECommon.hpp"
#include "TarcogConstants.hpp"
#include "HeatFlowBalance.hpp"
#include "IGU.hpp"

using namespace std;
using namespace FenestrationCommon;

namespace Tarcog {

  CNonLinearSolver::CNonLinearSolver( shared_ptr< CIGU > const & t_IGU ) : 
    m_IGU( t_IGU ), m_Tolerance( IterationConstants::CONVERGENCE_TOLERANCE ), m_Iterations( 0 ),
    m_RelaxParam( IterationConstants::RELAXATION_PARAMETER_MAX ){
    assert( t_IGU != nullptr );
    m_LinearSolver = make_shared< CLinearSolver >();
    assert( m_LinearSolver != nullptr );
    m_QBalance = make_shared< CHeatFlowBalance >( m_IGU );
    assert( m_QBalance != nullptr );
  }

  double CNonLinearSolver::calculateTolerance( vector< double > const & t_Solution ) const {
    assert(t_Solution.size() == m_IGUState->size() );
    auto aError = fabs( t_Solution[ 0 ] - ( *m_IGUState )[ 0 ] );
    for( size_t i = 1; i < m_IGUState->size(); ++i ) {
      aError = max( aError, fabs( t_Solution[ i ] - ( *m_IGUState )[ i ] ));
    }
    return aError;
  }

  void CNonLinearSolver::estimateNewState( vector< double > const & t_Solution ) const {
    assert(t_Solution.size() == m_IGUState->size() );
    for( size_t i = 0; i < m_IGUState->size(); ++i ) {
      ( *m_IGUState )[ i ] = m_RelaxParam * t_Solution[ i ] + ( 1 - m_RelaxParam ) * ( *m_IGUState )[ i ];
    }
  }

  void CNonLinearSolver::setTolerance( double const t_Tolerance ) {
    m_Tolerance = t_Tolerance;
  }

  size_t CNonLinearSolver::getNumOfIterations() const {
    return m_Iterations;
  }

  void CNonLinearSolver::solve() {
    m_IGUState = m_IGU->getState();
    vector< double > initialState( *m_IGUState );
    vector< double > bestSolution( m_IGUState->size() );
    assert( m_IGUState != nullptr );
    auto achievedTolerance = 1000.0;
    m_SolutionTolerance = achievedTolerance;

    m_Iterations = 0;
    bool iterate = true;

    while ( iterate ) {
      ++m_Iterations;
      vector< double > aSolution = m_QBalance->calcBalanceMatrix();

      achievedTolerance = calculateTolerance( aSolution );

      estimateNewState( aSolution );
      
      m_IGU->setState( *m_IGUState );

      if( achievedTolerance < m_SolutionTolerance ) {
        initialState = *m_IGUState;
        m_SolutionTolerance = min( achievedTolerance, m_SolutionTolerance );
        bestSolution = *m_IGUState;
      }

      if( m_Iterations > IterationConstants::NUMBER_OF_STEPS ) {
        m_Iterations = 0;
        m_RelaxParam -= IterationConstants::RELAXATION_PARAMETER_STEP;
        
        m_IGU->setState( initialState );
        *m_IGUState = initialState;
      }

      iterate = achievedTolerance > m_Tolerance;

      if( m_RelaxParam < IterationConstants::RELAXATION_PARAMETER_MIN ) {
        iterate = false;
      }

    }
    *m_IGUState = bestSolution;
  }

  double CNonLinearSolver::solutionTolerance() const {
    return m_SolutionTolerance;
  }

  bool CNonLinearSolver::isToleranceAchieved() const {
    return m_SolutionTolerance < m_Tolerance;
  }

}