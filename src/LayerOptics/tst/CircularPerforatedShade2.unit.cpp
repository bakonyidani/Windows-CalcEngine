#include <memory>
#include <gtest\gtest.h>

#include "UniformDiffuseBSDFLayer.hpp"
#include "PerforatedCell.hpp"
#include "PerforatedCellDescription.hpp"
#include "MaterialDescription.hpp"
#include "BSDFDirections.hpp"
#include "SquareMatrix.hpp"
#include "BSDFResults.hpp"
#include "FenestrationCommon.hpp"

using namespace std;
using namespace LayerOptics;
using namespace FenestrationCommon;

class TestCircularPerforatedShade2 : public testing::Test
{

private:
	shared_ptr< CUniformDiffuseBSDFLayer > m_Shade;

protected:
	virtual void SetUp() {
    // create material
    double Tmat = 0.2;
    double Rfmat = 0.8;
    double Rbmat = 0.8;
    double minLambda = 0.3;
    double maxLambda = 2.5;
    shared_ptr< CMaterialSingleBand > aMaterial = 
      make_shared< CMaterialSingleBand >( Tmat, Tmat, Rfmat, Rbmat, minLambda, maxLambda );

    // make cell geometry
    double x = 22.5; // mm
    double y = 38.1; // mm
    double thickness = 5; // mm
    double radius = 0; // mm
    shared_ptr< CCircularCellDescription > aCellDescription = 
      make_shared< CCircularCellDescription >( x, y, thickness, radius );

    shared_ptr< CBSDFHemisphere > aBSDF = make_shared< CBSDFHemisphere >( BSDFBasis::Quarter );

		shared_ptr< CPerforatedCell > aCell = make_shared< CPerforatedCell >( aMaterial, aCellDescription );
    
    m_Shade = make_shared< CUniformDiffuseBSDFLayer >( aCell, aBSDF );

	};

public:
	shared_ptr< CUniformDiffuseBSDFLayer > GetShade() { return m_Shade; };

};

TEST_F( TestCircularPerforatedShade2, TestSolarProperties )
{
	SCOPED_TRACE( "Begin Test: Circular perforated cell - Solar properties." );
	
	shared_ptr< CUniformDiffuseBSDFLayer > aShade = GetShade();

  shared_ptr< CBSDFResults > aResults = aShade->getResults();

  double tauDiff = aResults->TauDiff( Side::Front );
  EXPECT_NEAR( 0.2, tauDiff, 1e-6 );

  double RfDiff = aResults->RhoDiff( Side::Front );
  EXPECT_NEAR( 0.8, RfDiff, 1e-6 );

  double RbDiff = aResults->RhoDiff( Side::Back );
  EXPECT_NEAR( 0.8, RbDiff, 1e-6 );

  shared_ptr< CSquareMatrix > aT = aResults->Tau( Side::Front );

  size_t size = aT->getSize();

  // Test diagonal
  vector< double > correctResults;
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );

  vector< double > calculatedResults;
  for( int i = 0; i < size; ++i ) {
    calculatedResults.push_back( (*aT)[i][i] );
  }

  EXPECT_EQ( correctResults.size(), calculatedResults.size() );
  for( int i = 0; i < size; ++i ) {
    EXPECT_NEAR( correctResults[i], calculatedResults[i], 1e-5 );
  }

  // Test first row
  correctResults.clear();
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );

  calculatedResults.clear();
  for( int i = 0; i < size; ++i ) {
    calculatedResults.push_back( (*aT)[ 0 ][ i ] );
  }

  EXPECT_EQ( correctResults.size(), calculatedResults.size() );
  for( int i = 0; i < size; ++i ) {
    EXPECT_NEAR( correctResults[i], calculatedResults[i], 1e-5 );
  }

  // Test first row for reflectance matrix
  shared_ptr< CSquareMatrix > aRf = aResults->Rho( Side::Front );

  correctResults.clear();
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );

  calculatedResults.clear();
  for( int i = 0; i < size; ++i ) {
    calculatedResults.push_back( (*aRf)[ 0 ][ i ] );
  }

  EXPECT_EQ( correctResults.size(), calculatedResults.size() );
  for( int i = 0; i < size; ++i ) {
    EXPECT_NEAR( correctResults[i], calculatedResults[i], 1e-5 );
  }

  // Test first row for reflectance matrix
  shared_ptr< CSquareMatrix > aRb = aResults->Rho( Side::Back );

  correctResults.clear();
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );
  correctResults.push_back( 0.254648 );

  calculatedResults.clear();
  for( int i = 0; i < size; ++i ) {
    calculatedResults.push_back( (*aRb)[ 0 ][ i ] );
  }

  EXPECT_EQ( correctResults.size(), calculatedResults.size() );
  for( int i = 0; i < size; ++i ) {
    EXPECT_NEAR( correctResults[i], calculatedResults[i], 1e-5 );
  }

}