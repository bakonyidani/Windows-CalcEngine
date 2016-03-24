#include <memory>
#include <gtest\gtest.h>

#include "DirectionalDiffuseBSDFLayer.hpp"
#include "VenetianCell.hpp"
#include "VenetianCellDescription.hpp"
#include "MaterialDescription.hpp"
#include "FenestrationCommon.hpp"
#include "BSDFDirections.hpp"
#include "BSDFResults.hpp"
#include "SquareMatrix.hpp"

using namespace std;
using namespace LayerOptics;
using namespace FenestrationCommon;

class TestVenetianDirectionalShadeFlat0_1 : public testing::Test {

private:
	shared_ptr< CDirectionalDiffuseBSDFLayer > m_Shade;

protected:
	virtual void SetUp() {
    // create material
    double Tmat = 0.1;
    double Rfmat = 0.7;
    double Rbmat = 0.7;
    double minLambda = 0.3;
    double maxLambda = 2.5;
    shared_ptr< CMaterialSingleBand > aMaterial = 
      make_shared< CMaterialSingleBand >( Tmat, Tmat, Rfmat, Rbmat, minLambda, maxLambda );
    
    // make cell geometry
    double slatWidth = 0.010; // m
    double slatSpacing = 0.010; // m
    double slatTiltAngle = 45;
    double curvatureRadius = 0;
    size_t numOfSlatSegments = 1;

    shared_ptr< CVenetianCellDescription > aCellDescription = 
      make_shared< CVenetianCellDescription >( slatWidth, slatSpacing, slatTiltAngle, 
      curvatureRadius, numOfSlatSegments );

    shared_ptr< CVenetianCell > aCell = make_shared< CVenetianCell >( aMaterial, aCellDescription );

    shared_ptr< CBSDFHemisphere > aBSDF = make_shared< CBSDFHemisphere >( BSDFBasis::Quarter );

    m_Shade = make_shared< CDirectionalDiffuseBSDFLayer >( aCell, aBSDF );

	};

public:
	shared_ptr< CDirectionalDiffuseBSDFLayer > GetShade() { return m_Shade; };

};

TEST_F( TestVenetianDirectionalShadeFlat0_1, TestVenetian1 ) {
	SCOPED_TRACE( "Begin Test: Venetian cell (Flat, 45 degrees slats) - solar properties." );
	
	shared_ptr< CDirectionalDiffuseBSDFLayer > aShade = GetShade();

  shared_ptr< CBSDFResults > aResults = aShade->getResults();

  double tauDiff = aResults->TauDiff( Side::Front );
  EXPECT_NEAR( 0.44649813630049223, tauDiff, 1e-6 );

  double RfDiff = aResults->RhoDiff( Side::Front );
  EXPECT_NEAR( 0.28386835793952669, RfDiff, 1e-6 );

  shared_ptr< CSquareMatrix > aT = aResults->Tau( Side::Front );

  // Test only diagonal of transmittance matrix
  size_t size = aT->getSize();

  vector< double > correctResults;
  correctResults.push_back( 3.8537531201195208 );
  correctResults.push_back( 4.1502982467458276 );
  correctResults.push_back( 6.4100346243744326 );
  correctResults.push_back( 7.3474092442895333 );
  correctResults.push_back( 6.4100346243744326 );
  correctResults.push_back( 4.1502982467458276 );
  correctResults.push_back( 1.8952091768254709 );
  correctResults.push_back( 0.9624818646186141 );
  correctResults.push_back( 1.8952091768254709 );
  correctResults.push_back( 3.8507492805553354 );
  correctResults.push_back( 7.1631325677152899 );
  correctResults.push_back( 9.5953311156279479 );
  correctResults.push_back( 10.487134124145857 );
  correctResults.push_back( 9.5953311156279479 );
  correctResults.push_back( 7.1631325677152899 );
  correctResults.push_back( 3.8507492805553367 );
  correctResults.push_back( 0.5499842626659959 );
  correctResults.push_back( 0.076422070782678389 );
  correctResults.push_back( 0.072113581483518790 );
  correctResults.push_back( 0.076422070782678389 );
  correctResults.push_back( 0.54998426266599365 );
  correctResults.push_back( 3.8507492805553394 );
  correctResults.push_back( 10.135661402447086 );
  correctResults.push_back( 11.234248057098451 );
  correctResults.push_back( 9.5441761716221478 );
  correctResults.push_back( 11.234248057098451 );
  correctResults.push_back( 10.135661402447086 );
  correctResults.push_back( 3.8507492805553412 );
  correctResults.push_back( 0.073751825599575688 );
  correctResults.push_back( 0.056801188075067718 );
  correctResults.push_back( 0.052393583794556338 );
  correctResults.push_back( 0.056801188075067677 );
  correctResults.push_back( 0.073751825599575660 );
  correctResults.push_back( 3.6627476023802092 );
  correctResults.push_back( 0.064003709245804577 );
  correctResults.push_back( 0.039335031220287420 );
  correctResults.push_back( 0.064003709245804577 );
  correctResults.push_back( 3.6627476023802141 );
  correctResults.push_back( 0.031558258087563060 );
  correctResults.push_back( 0.024104538133300955 );
  correctResults.push_back( 0.031558258087563032 );

  vector< double > calculatedResults;
  for( int i = 0; i < size; ++i ) {
    calculatedResults.push_back( (*aT)[i][i] );
  }

  EXPECT_EQ( correctResults.size(), calculatedResults.size() );
  for( int i = 0; i < size; ++i ) {
    EXPECT_NEAR( correctResults[i], calculatedResults[i], 1e-5 );
  }

  // Front reflectance
  shared_ptr< CSquareMatrix > aRf = aResults->Rho( Side::Front );

  correctResults.clear();
  calculatedResults.clear();

  correctResults.push_back( 0.12467701187757886 );
  correctResults.push_back( 0.12467701187757886 );
  correctResults.push_back( 0.11809576069675247 );
  correctResults.push_back( 0.11151450951592602 );
  correctResults.push_back( 0.11809576069675243 );
  correctResults.push_back( 0.12467701187757889 );
  correctResults.push_back( 0.11809576069675248 );
  correctResults.push_back( 0.11151450951592602 );
  correctResults.push_back( 0.11809576069675248 );
  correctResults.push_back( 0.12467701187757886 );
  correctResults.push_back( 0.10822388392551284 );
  correctResults.push_back( 0.056751264415241136 );
  correctResults.push_back( 0.039493797495131787 );
  correctResults.push_back( 0.056751264415241136 );
  correctResults.push_back( 0.10822388392551285 );
  correctResults.push_back( 0.12467701187757889 );
  correctResults.push_back( 0.10822388392551291 );
  correctResults.push_back( 0.065378671009513112 );
  correctResults.push_back( 0.048215999889970981 );
  correctResults.push_back( 0.065378671009513042 );
  correctResults.push_back( 0.10822388392551284 );
  correctResults.push_back( 0.12467701187757886 );
  correctResults.push_back( 0.046055713210097007 );
  correctResults.push_back( 0.0077108503397755159 );
  correctResults.push_back( 0.013944144090848406 );
  correctResults.push_back( 0.0077108503397755150 );
  correctResults.push_back( 0.046055713210097007 );
  correctResults.push_back( 0.12467701187757892 );
  correctResults.push_back( 0.054978145293713886 );
  correctResults.push_back( 0.011951549151406803 );
  correctResults.push_back( 0.023431122989891869 );
  correctResults.push_back( 0.011951549151406849 );
  correctResults.push_back( 0.054978145293713775 );
  correctResults.push_back( 0.12467701187757879 );
  correctResults.push_back( 0.031558258087563046 );
  correctResults.push_back( 0.024104538133300962 );
  correctResults.push_back( 0.031558258087563046 );
  correctResults.push_back( 0.12467701187757896 );
  correctResults.push_back( 0.064003709245804660 );
  correctResults.push_back( 0.039335031220287427 );
  correctResults.push_back( 0.064003709245804577 );

  for( int i = 0; i < size; ++i ) {
    calculatedResults.push_back( (*aRf)[i][i] );
  }

  EXPECT_EQ( correctResults.size(), calculatedResults.size() );
  for( int i = 0; i < size; ++i ) {
    EXPECT_NEAR( correctResults[i], calculatedResults[i], 1e-5 );
  }

}