#include <assert.h>
#include <math.h>
#include <algorithm>

#include "TarNonLinearSolver.hpp"
#include "TarcogConstants.hpp"
#include "LinearSolver.hpp"
#include "TarcogQBalance.hpp"
#include "TarIGU.hpp"

using namespace std;
using namespace FenestrationCommon;

namespace Tarcog {

  CTarNonLinearSolver::CTarNonLinearSolver( shared_ptr< CTarIGU > const t_IGU ) : m_IGU( t_IGU )  {
    assert( t_IGU != nullptr );
    m_LinearSolver = make_shared< CLinearSolver >();
    assert( m_LinearSolver != nullptr );
    m_QBalance = make_shared< CTarcogQBalance >( m_IGU );
    assert( m_QBalance != nullptr );
    m_IGUState = m_IGU->getState();
    assert( m_IGUState != nullptr );
    m_RelaxParam = IterationConstants::RELAXATION_PARAMETER_MAX;
    m_Tolerance = IterationConstants::CONVERGENCE_TOLERANCE;
    m_Iterations = 0;
  }

  double CTarNonLinearSolver::calculateTolerance( shared_ptr< vector< double > > t_Solution ) {
    assert(t_Solution->size() == m_IGUState->size() );
    double aError = fabs( ( *t_Solution )[ 0 ] - ( *m_IGUState )[ 0 ] );
    for( size_t i = 1; i < m_IGUState->size(); ++i ) {
      aError = max( aError, fabs( ( *t_Solution )[ i ] - ( *m_IGUState )[ i ] ));
    }
    return aError;
  };

  void CTarNonLinearSolver::estimateNewState( shared_ptr< vector< double > > t_Solution ) {
    assert(t_Solution->size() == m_IGUState->size() );
    for( size_t i = 0; i < m_IGUState->size(); ++i ) {
      ( *m_IGUState )[ i ] = m_RelaxParam * ( *t_Solution )[ i ] + ( 1 - m_RelaxParam ) * ( *m_IGUState )[ i ];
    }
  };

  void CTarNonLinearSolver::solve() {
    shared_ptr< vector< double > > aSolution = nullptr;
    double achievedTolerance = 1;
    m_Iterations = 0;

    while ( achievedTolerance > m_Tolerance ) {
      ++m_Iterations;
      aSolution = m_QBalance->calcBalanceMatrix();
      assert( aSolution != nullptr );

      achievedTolerance = calculateTolerance( aSolution );

      estimateNewState( aSolution );

      m_IGU->setState( m_IGUState );

    }
  };

}