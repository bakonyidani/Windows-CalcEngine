#define _USE_MATH_DEFINES
#include <math.h>
#include <numeric>
#include <algorithm>
#include <assert.h>

#include "MultiBSDFLayer.hpp"
#include "BSDFIntegrator.hpp"
#include "EquivalentBSDFLayer.hpp"
#include "Series.hpp"
#include "IntegratorStrategy.hpp"
#include "FenestrationCommon.hpp"
#include "MatrixSeries.hpp"
#include "BSDFDirections.hpp"

using namespace std;
using namespace FenestrationCommon;
using namespace SingleLayerOptics;

namespace MultiLayerOptics {

  CMultiBSDFLayer::CMultiBSDFLayer( const shared_ptr< CEquivalentBSDFLayer >& t_Layer, 
    const p_Series& t_SolarRadiation, const p_VectorSeries& t_IncomingSpectra ) : 
    m_Layer( t_Layer ), m_SolarRadiationInit( t_SolarRadiation ),
    m_Results( make_shared< CBSDFIntegrator >( t_Layer->getDirections( BSDFHemisphere::Incoming ) ) ), 
    m_Calculated( false ), m_MinLambdaCalculated( 0 ), m_MaxLambdaCalculated( 0 ) {

    for( Side aSide : EnumSide() ) {
      m_AbsHem[ aSide ] = make_shared< vector< double > >();
    }

    // This will initialize layer material data with given spectral distribution
    t_Layer->setSolarRadiation( m_SolarRadiationInit );

    size_t directionsSize = t_Layer->getDirections( BSDFHemisphere::Incoming )->size();
    m_IncomingSolar.resize( directionsSize );
    if( t_IncomingSpectra != nullptr ) {
      if( t_IncomingSpectra->size() != directionsSize ) {
        throw runtime_error("Provided spectra size does not match BSDF of the layers.");
      }
      m_IncomingSpectra = t_IncomingSpectra;
    } else {
      // For blank incoming spectra, defaults needs to be filled into
      m_IncomingSpectra = make_shared< vector< p_Series > >();
      for( size_t i = 0; i < directionsSize; ++i ) {
        m_IncomingSpectra->push_back( t_SolarRadiation );
      }
    }
  }

  shared_ptr< CSquareMatrix > CMultiBSDFLayer::getMatrix( const double minLambda, const double maxLambda,
    const Side t_Side, const PropertySimple t_Property ) {
    calculate( minLambda, maxLambda );

    return m_Results->getMatrix( t_Side, t_Property );
  }

  double CMultiBSDFLayer::DirDir( const double minLambda, const double maxLambda,
    const Side t_Side, const PropertySimple t_Property, const double t_Theta, const double t_Phi ) {
    calculate( minLambda, maxLambda );

    return m_Results->DirDir( t_Side, t_Property, t_Theta, t_Phi );
  }

  void CMultiBSDFLayer::calculate( const double minLambda, const double maxLambda ) {
    if( !m_Calculated || minLambda != m_MinLambdaCalculated || maxLambda != m_MaxLambdaCalculated ) {
      m_IncomingSolar.clear();

      for( shared_ptr< CSeries >& aSpectra : *m_IncomingSpectra ) {
        // each incoming spectra must be intepolated to same wavelengths as this IGU is using
        aSpectra = aSpectra->interpolate( *m_Layer->getCommonWavelengths() );

        shared_ptr< CSeries > iTotalSolar = aSpectra->integrate( IntegrationType::Trapezoidal );
        m_IncomingSolar.push_back( iTotalSolar->sum( minLambda, maxLambda ) );
      }

      // Produce local results matrices for each side and property
      map < pair< Side, PropertySimple >, shared_ptr< CSquareMatrix > > aResults;

      for( Side aSide : EnumSide() ) {
        CMatrixSeries aTotalA = *m_Layer->getTotalA( aSide );
        aTotalA.mMult( *m_IncomingSpectra );
        aTotalA.integrate( IntegrationType::Trapezoidal );
        m_Abs[ aSide ] = aTotalA.getSums( minLambda, maxLambda, m_IncomingSolar );
        for( PropertySimple aProprerty : EnumPropertySimple() ) {
          CMatrixSeries aTot = *m_Layer->getTotal( aSide, aProprerty );
          aTot.mMult( *m_IncomingSpectra );
          aTot.integrate( IntegrationType::Trapezoidal );
          aResults[ make_pair( aSide, aProprerty ) ] =
            aTot.getSquaredMatrixSums( minLambda, maxLambda, m_IncomingSolar );
        }

        // Update result matrices
        m_Results->setResultMatrices( aResults.at( make_pair( aSide, PropertySimple::T ) ),
          aResults.at( make_pair( aSide, PropertySimple::R ) ), aSide );
      }

      // calculate hemispherical absorptances
      for( Side aSide : EnumSide() ) {
        calcHemisphericalAbs( aSide );
      }

      m_MinLambdaCalculated = minLambda;
      m_MaxLambdaCalculated = maxLambda;
      m_Calculated = true;
    }
  }

  void CMultiBSDFLayer::calcHemisphericalAbs( const Side t_Side ) {
    size_t numOfLayers = m_Abs[ t_Side ]->size();
    vector< double > aLambdas = *m_Results->lambdaVector();
    for( size_t layNum = 0; layNum < numOfLayers; ++layNum ) {
      vector< double > aAbs = *( *m_Abs[ t_Side ] )[ layNum ];
      assert( aAbs.size() == aLambdas.size() );
      vector< double > mult( aLambdas.size() );
      transform( aLambdas.begin(), aLambdas.end(), aAbs.begin(), mult.begin(), multiplies< double >() );
      double sum = accumulate( mult.begin(), mult.end(), 0.0 ) / M_PI;
      m_AbsHem[ t_Side ]->push_back( sum );
    }
  }

  shared_ptr< vector< double > > CMultiBSDFLayer::Abs( const double minLambda, const double maxLambda,
    const Side t_Side, const size_t Index ) {
    calculate( minLambda, maxLambda );
    return ( *m_Abs.at( t_Side ) )[ Index - 1 ];
  }

  shared_ptr< vector< double > > CMultiBSDFLayer::DirHem( const double minLambda, const double maxLambda,
    const Side t_Side, const PropertySimple t_Property ) {
    calculate( minLambda, maxLambda );
    return m_Results->DirHem( t_Side, t_Property );
  }

  double CMultiBSDFLayer::DirHem( const double minLambda, const double maxLambda,
    const Side t_Side, const PropertySimple t_Property,
    const double t_Theta, const double t_Phi ) {
    auto aIndex = m_Results->getNearestBeamIndex( t_Theta, t_Phi );
    return ( *DirHem( minLambda, maxLambda, t_Side, t_Property ) )[ aIndex ];
  }

  double CMultiBSDFLayer::Abs( const double minLambda, const double maxLambda,
    const Side t_Side, const size_t Index, const double t_Theta, const double t_Phi ) {
    auto aIndex = m_Results->getNearestBeamIndex( t_Theta, t_Phi );
    return ( *Abs( minLambda, maxLambda, t_Side, Index ) )[ aIndex ];
  }

  double CMultiBSDFLayer::DiffDiff( const double minLambda, const double maxLambda,
    const Side t_Side, const PropertySimple t_Property ) {
    calculate( minLambda, maxLambda );
    return m_Results->DiffDiff( t_Side, t_Property );
  }

  double CMultiBSDFLayer::AbsDiff( const double minLambda, const double maxLambda,
    const Side t_Side, const size_t t_LayerIndex ) {
    calculate( minLambda, maxLambda );
    return ( *m_AbsHem[ t_Side ] )[ t_LayerIndex - 1 ];
  }

  double CMultiBSDFLayer::energy( const double minLambda, const double maxLambda, 
    const Side t_Side, const PropertySimple t_Property, const double t_Theta, const double t_Phi ) {
    calculate( minLambda, maxLambda );
    auto aIndex = m_Results->getNearestBeamIndex( t_Theta, t_Phi );
    double solarRadiation = m_IncomingSolar[ aIndex ];
    double dirHem = ( *DirHem( minLambda, maxLambda, t_Side, t_Property ) )[ aIndex ];
    return dirHem * solarRadiation;
  }

  double CMultiBSDFLayer::energyAbs( const double minLambda, const double maxLambda, 
    const Side t_Side, const size_t Index, const double t_Theta, const double t_Phi ) {
    calculate( minLambda, maxLambda );
    auto aIndex = m_Results->getNearestBeamIndex( t_Theta, t_Phi );
    double solarRadiation = m_IncomingSolar[ aIndex ];
    double abs = ( *Abs( minLambda, maxLambda, t_Side, Index ) )[ aIndex ];
    return abs * solarRadiation;
  }

}