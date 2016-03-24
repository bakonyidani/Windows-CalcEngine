#include <memory>
#include <gtest\gtest.h>

#include "UniformDiffuseBSDFLayer.hpp"
#include "PerforatedCell.hpp"
#include "PerforatedCellDescription.hpp"
#include "MaterialDescription.hpp"
#include "FenestrationCommon.hpp"
#include "BSDFDirections.hpp"
#include "BSDFResults.hpp"
#include "SquareMatrix.hpp"

using namespace std;
using namespace LayerOptics;
using namespace FenestrationCommon;
using namespace SpectralAveraging;

class TestCircularPerforatedShadeMultiWavelength : public testing::Test {

private:
	shared_ptr< CUniformDiffuseBSDFLayer > m_Layer;

protected:
	virtual void SetUp() {
    // Solar range material
    double Tmat = 0.1;
    double Rfmat = 0.7;
    double Rbmat = 0.7;
    double minLambda = 0.3;
    double maxLambda = 2.5;
    shared_ptr< CMaterialSingleBand > aSolarRangeMaterial = 
      make_shared< CMaterialSingleBand >( Tmat, Tmat, Rfmat, Rbmat, minLambda, maxLambda );

    // Visible range
    Tmat = 0.2;
    Rfmat = 0.6;
    Rbmat = 0.6;
    minLambda = 0.38;
    maxLambda = 0.78;
    shared_ptr< CMaterialSingleBand > aVisibleRangeMaterial = 
      make_shared< CMaterialSingleBand >( Tmat, Tmat, Rfmat, Rbmat, minLambda, maxLambda );

    double ratio = 0.49;

    shared_ptr< CMaterialDualBand > aMaterial = 
      make_shared< CMaterialDualBand >( aVisibleRangeMaterial, aSolarRangeMaterial, ratio );

    // make cell geometry
    double x = 22.5; // mm
    double y = 38.1; // mm
    double thickness = 5; // mm
    double radius = 8.35; // mm
    shared_ptr< CCircularCellDescription > aCellDescription = 
      make_shared< CCircularCellDescription >( x, y, thickness, radius );

    shared_ptr< CBSDFHemisphere > aBSDF = make_shared< CBSDFHemisphere >( BSDFBasis::Quarter );

		shared_ptr< CPerforatedCell > aCell = make_shared< CPerforatedCell >( aMaterial, aCellDescription );

    m_Layer = make_shared< CUniformDiffuseBSDFLayer >( aCell, aBSDF );

	};

public:
	shared_ptr< CUniformDiffuseBSDFLayer > getLayer() { return m_Layer; };

};

TEST_F( TestCircularPerforatedShadeMultiWavelength, TestCircularPerforatedMultiWavelength ) {
	SCOPED_TRACE( "Begin Test: Perforated layer (multi range) - BSDF." );
	
	shared_ptr< CUniformDiffuseBSDFLayer > aLayer = getLayer();

  shared_ptr< vector< shared_ptr< CBSDFResults > > > aResults = aLayer->getWavelengthResults();

  EXPECT_EQ( 4, aResults->size() );

  ///////////////////////////////////////////////////////////////////////
  //  Wavelength number 1
  ///////////////////////////////////////////////////////////////////////

  shared_ptr< CSquareMatrix > aT = ( *aResults )[ 0 ]->Tau( Side::Front );

  // Test only diagonal of transmittance matrix
  size_t size = aT->getSize();

  vector< double > correctResults;
  correctResults.push_back( 3.323538 );
  correctResults.push_back( 3.233753 );
  correctResults.push_back( 3.233753 );
  correctResults.push_back( 3.233753 );
  correctResults.push_back( 3.233753 );
  correctResults.push_back( 3.233753 );
  correctResults.push_back( 3.233753 );
  correctResults.push_back( 3.233753 );
  correctResults.push_back( 3.233753 );
  correctResults.push_back( 2.598526 );
  correctResults.push_back( 2.598526 );
  correctResults.push_back( 2.598526 );
  correctResults.push_back( 2.598526 );
  correctResults.push_back( 2.598526 );
  correctResults.push_back( 2.598526 );
  correctResults.push_back( 2.598526 );
  correctResults.push_back( 2.598526 );
  correctResults.push_back( 2.598526 );
  correctResults.push_back( 2.598526 );
  correctResults.push_back( 2.598526 );
  correctResults.push_back( 2.598526 );
  correctResults.push_back( 1.952399 );
  correctResults.push_back( 1.952399 );
  correctResults.push_back( 1.952399 );
  correctResults.push_back( 1.952399 );
  correctResults.push_back( 1.952399 );
  correctResults.push_back( 1.952399 );
  correctResults.push_back( 1.952399 );
  correctResults.push_back( 1.952399 );
  correctResults.push_back( 1.952399 );
  correctResults.push_back( 1.952399 );
  correctResults.push_back( 1.952399 );
  correctResults.push_back( 1.952399 );
  correctResults.push_back( 0.000000 );
  correctResults.push_back( 0.000000 );
  correctResults.push_back( 0.000000 );
  correctResults.push_back( 0.000000 );
  correctResults.push_back( 0.000000 );
  correctResults.push_back( 0.000000 );
  correctResults.push_back( 0.000000 );
  correctResults.push_back( 0.000000 );

  vector< double > calculatedResults;
  for( int i = 0; i < size; ++i ) {
    calculatedResults.push_back( (*aT)[i][i] );
  }

  EXPECT_EQ( correctResults.size(), calculatedResults.size() );
  for( int i = 0; i < size; ++i ) {
    EXPECT_NEAR( correctResults[i], calculatedResults[i], 1e-5 );
  }

  // Front reflectance
  shared_ptr< CSquareMatrix > aRf = ( *aResults )[ 0 ]->Rho( Side::Front );

  correctResults.clear();
  calculatedResults.clear();

  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );
  correctResults.push_back( 0 );

  for( int i = 0; i < size; ++i ) {
    calculatedResults.push_back( (*aRf)[i][i] );
  }

  EXPECT_EQ( correctResults.size(), calculatedResults.size() );
  for( int i = 0; i < size; ++i ) {
    EXPECT_NEAR( correctResults[i], calculatedResults[i], 1e-5 );
  }

  ///////////////////////////////////////////////////////////////////////
  //  Wavelength number 2
  ///////////////////////////////////////////////////////////////////////

  aT = ( *aResults )[ 1 ]->Tau( Side::Front );

  // Test only diagonal of transmittance matrix
  size = aT->getSize();

  correctResults.clear();
  calculatedResults.clear();

  correctResults.push_back( 3.324467 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 0.001248 );
  correctResults.push_back( 0.001248 );
  correctResults.push_back( 0.001248 );
  correctResults.push_back( 0.001248 );
  correctResults.push_back( 0.001248 );
  correctResults.push_back( 0.001248 );
  correctResults.push_back( 0.001248 );
  correctResults.push_back( 0.001248 );

  for( int i = 0; i < size; ++i ) {
    calculatedResults.push_back( (*aT)[i][i] );
  }

  EXPECT_EQ( correctResults.size(), calculatedResults.size() );
  for( int i = 0; i < size; ++i ) {
    EXPECT_NEAR( correctResults[i], calculatedResults[i], 1e-5 );
  }

  // Front reflectance
  aRf = ( *aResults )[ 1 ]->Rho( Side::Front );

  correctResults.clear();
  calculatedResults.clear();

  correctResults.push_back( 0.188652 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.253400 );
  correctResults.push_back( 0.253400 );
  correctResults.push_back( 0.253400 );
  correctResults.push_back( 0.253400 );
  correctResults.push_back( 0.253400 );
  correctResults.push_back( 0.253400 );
  correctResults.push_back( 0.253400 );
  correctResults.push_back( 0.253400 );

  for( int i = 0; i < size; ++i ) {
    calculatedResults.push_back( (*aRf)[i][i] );
  }

  EXPECT_EQ( correctResults.size(), calculatedResults.size() );
  for( int i = 0; i < size; ++i ) {
    EXPECT_NEAR( correctResults[i], calculatedResults[i], 1e-5 );
  }

  ///////////////////////////////////////////////////////////////////////
  //  Wavelength number 3
  ///////////////////////////////////////////////////////////////////////

  aT = ( *aResults )[ 2 ]->Tau( Side::Front );

  // Test only diagonal of transmittance matrix
  size = aT->getSize();

  correctResults.clear();
  calculatedResults.clear();

  correctResults.push_back( 3.370933 );
  correctResults.push_back( 3.282731 );
  correctResults.push_back( 3.282731 );
  correctResults.push_back( 3.282731 );
  correctResults.push_back( 3.282731 );
  correctResults.push_back( 3.282731 );
  correctResults.push_back( 3.282731 );
  correctResults.push_back( 3.282731 );
  correctResults.push_back( 3.282731 );
  correctResults.push_back( 2.649460 );
  correctResults.push_back( 2.649460 );
  correctResults.push_back( 2.649460 );
  correctResults.push_back( 2.649460 );
  correctResults.push_back( 2.649460 );
  correctResults.push_back( 2.649460 );
  correctResults.push_back( 2.649460 );
  correctResults.push_back( 2.649460 );
  correctResults.push_back( 2.649460 );
  correctResults.push_back( 2.649460 );
  correctResults.push_back( 2.649460 );
  correctResults.push_back( 2.649460 );
  correctResults.push_back( 2.006498 );
  correctResults.push_back( 2.006498 );
  correctResults.push_back( 2.006498 );
  correctResults.push_back( 2.006498 );
  correctResults.push_back( 2.006498 );
  correctResults.push_back( 2.006498 );
  correctResults.push_back( 2.006498 );
  correctResults.push_back( 2.006498 );
  correctResults.push_back( 2.006498 );
  correctResults.push_back( 2.006498 );
  correctResults.push_back( 2.006498 );
  correctResults.push_back( 2.006498 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );
  correctResults.push_back( 0.063662 );

  for( int i = 0; i < size; ++i ) {
    calculatedResults.push_back( (*aT)[i][i] );
  }

  EXPECT_EQ( correctResults.size(), calculatedResults.size() );
  for( int i = 0; i < size; ++i ) {
    EXPECT_NEAR( correctResults[i], calculatedResults[i], 1e-5 );
  }

  // Front reflectance
  aRf = ( *aResults )[ 2 ]->Rho( Side::Front );

  correctResults.clear();
  calculatedResults.clear();

  correctResults.push_back( 0.142186 );
  correctResults.push_back( 0.146934 );
  correctResults.push_back( 0.146934 );
  correctResults.push_back( 0.146934 );
  correctResults.push_back( 0.146934 );
  correctResults.push_back( 0.146934 );
  correctResults.push_back( 0.146934 );
  correctResults.push_back( 0.146934 );
  correctResults.push_back( 0.146934 );
  correctResults.push_back( 0.152802 );
  correctResults.push_back( 0.152802 );
  correctResults.push_back( 0.152802 );
  correctResults.push_back( 0.152802 );
  correctResults.push_back( 0.152802 );
  correctResults.push_back( 0.152802 );
  correctResults.push_back( 0.152802 );
  correctResults.push_back( 0.152802 );
  correctResults.push_back( 0.152802 );
  correctResults.push_back( 0.152802 );
  correctResults.push_back( 0.152802 );
  correctResults.push_back( 0.152802 );
  correctResults.push_back( 0.162296 );
  correctResults.push_back( 0.162296 );
  correctResults.push_back( 0.162296 );
  correctResults.push_back( 0.162296 );
  correctResults.push_back( 0.162296 );
  correctResults.push_back( 0.162296 );
  correctResults.push_back( 0.162296 );
  correctResults.push_back( 0.162296 );
  correctResults.push_back( 0.162296 );
  correctResults.push_back( 0.162296 );
  correctResults.push_back( 0.162296 );
  correctResults.push_back( 0.162296 );
  correctResults.push_back( 0.190986 );
  correctResults.push_back( 0.190986 );
  correctResults.push_back( 0.190986 );
  correctResults.push_back( 0.190986 );
  correctResults.push_back( 0.190986 );
  correctResults.push_back( 0.190986 );
  correctResults.push_back( 0.190986 );
  correctResults.push_back( 0.190986 );

  for( int i = 0; i < size; ++i ) {
    calculatedResults.push_back( (*aRf)[i][i] );
  }

  EXPECT_EQ( correctResults.size(), calculatedResults.size() );
  for( int i = 0; i < size; ++i ) {
    EXPECT_NEAR( correctResults[i], calculatedResults[i], 1e-5 );
  }

  ///////////////////////////////////////////////////////////////////////
  //  Wavelength number 4
  ///////////////////////////////////////////////////////////////////////

  aT = ( *aResults )[ 3 ]->Tau( Side::Front );

  // Test only diagonal of transmittance matrix
  size = aT->getSize();

  correctResults.clear();
  calculatedResults.clear();

  correctResults.push_back( 3.324467 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 3.234714 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 2.599525 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 1.953460 );
  correctResults.push_back( 0.001248 );
  correctResults.push_back( 0.001248 );
  correctResults.push_back( 0.001248 );
  correctResults.push_back( 0.001248 );
  correctResults.push_back( 0.001248 );
  correctResults.push_back( 0.001248 );
  correctResults.push_back( 0.001248 );
  correctResults.push_back( 0.001248 );

  for( int i = 0; i < size; ++i ) {
    calculatedResults.push_back( (*aT)[i][i] );
  }

  EXPECT_EQ( correctResults.size(), calculatedResults.size() );
  for( int i = 0; i < size; ++i ) {
    EXPECT_NEAR( correctResults[i], calculatedResults[i], 1e-5 );
  }

  // Front reflectance
  aRf = ( *aResults )[ 3 ]->Rho( Side::Front );

  correctResults.clear();
  calculatedResults.clear();

  correctResults.push_back( 0.188652 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.194951 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.202737 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.215334 );
  correctResults.push_back( 0.253400 );
  correctResults.push_back( 0.253400 );
  correctResults.push_back( 0.253400 );
  correctResults.push_back( 0.253400 );
  correctResults.push_back( 0.253400 );
  correctResults.push_back( 0.253400 );
  correctResults.push_back( 0.253400 );
  correctResults.push_back( 0.253400 );

  for( int i = 0; i < size; ++i ) {
    calculatedResults.push_back( (*aRf)[i][i] );
  }

  EXPECT_EQ( correctResults.size(), calculatedResults.size() );
  for( int i = 0; i < size; ++i ) {
    EXPECT_NEAR( correctResults[i], calculatedResults[i], 1e-5 );
  }

}