#include <memory>
#include <gtest\gtest.h>

#include "TarOutdoorEnvironment.hpp"
#include "TarIndoorEnvironment.hpp"
#include "TarIGUSolidLayer.hpp"
#include "TarBaseShade.hpp"
#include "TarIGUGapLayer.hpp"
#include "TarIGU.hpp"
#include "TarcogSystem.hpp"

using namespace std;
using namespace Tarcog;

class TestGapLayerInBetweenVentilation : public testing::Test
{

private:
	shared_ptr< CTarIGUGapLayer > m_GapLayer1;
  shared_ptr< CTarIGUGapLayer > m_GapLayer2;
  shared_ptr< CTarcogSystem > m_TarcogSystem;

protected:
	virtual void SetUp()
	{
    try {

      /////////////////////////////////////////////////////////
      // Outdoor
      /////////////////////////////////////////////////////////
      double airTemperature = 255.15; // Kelvins
      double pressure = 101325; // Pascals
      double airSpeed = 5.5; // meters per second
      AirHorizontalDirection airDirection = AirHorizontalDirection::Windward;
      double tSky = 255.15; // Kelvins

      shared_ptr< CTarOutdoorEnvironment > Outdoor = 
        make_shared< CTarOutdoorEnvironment >( airTemperature, pressure, airSpeed, airDirection );
      ASSERT_TRUE( Outdoor != nullptr );
      Outdoor->setSkyTemperature( tSky );
      Outdoor->setHCoeffModel( BoundaryConditionsCoeffModel::CalculateH );
      Outdoor->setSkyModel( SkyModel::AllSpecified );

      /////////////////////////////////////////////////////////
      // Indoor
      /////////////////////////////////////////////////////////

      double roomTemperature = 295.15;
      double roomAirSpeed = 0;

      shared_ptr< CTarIndoorEnvironment > Indoor = 
        make_shared< CTarIndoorEnvironment > ( roomTemperature, pressure, roomAirSpeed, airDirection );
      ASSERT_TRUE( Indoor != nullptr );

      // IGU
      double solidLayerThickness = 0.005715; // [m]
      double solidLayerConductance = 1;

      shared_ptr< CTarIGUSolidLayer > SolidLayer1 = make_shared< CTarIGUSolidLayer > ( solidLayerThickness, solidLayerConductance );
      ASSERT_TRUE( SolidLayer1 != nullptr );

      shared_ptr< CTarIGUSolidLayer > SolidLayer2 = make_shared< CTarIGUSolidLayer > ( solidLayerThickness, solidLayerConductance );
      ASSERT_TRUE( SolidLayer2 != nullptr );

      double shadeLayerThickness = 0.01;
      double shadeLayerConductance = 160;
      double Atop = 0.1;
      double Abot = 0.1;
      double Aleft = 0.1;
      double Aright = 0.1;
      double Afront = 0.2;

      shared_ptr< CTarIGUShadeLayer > shadeLayer = make_shared< CTarIGUShadeLayer >( shadeLayerThickness, shadeLayerConductance,
        make_shared< CShadeOpenings >( Atop, Abot, Aleft, Aright, Afront ) );

      ASSERT_TRUE( shadeLayer != nullptr );

      double gapThickness = 0.0127;
      double gapPressure = 101325;
      m_GapLayer1 = make_shared< CTarIGUGapLayer >( gapThickness, gapPressure );
      ASSERT_TRUE( m_GapLayer1 != nullptr );

      m_GapLayer2 = make_shared< CTarIGUGapLayer >( gapThickness, gapPressure );
      ASSERT_TRUE( m_GapLayer2 != nullptr );

      double windowWidth = 1;
      double windowHeight = 1;
      shared_ptr< CTarIGU > aIGU = make_shared< CTarIGU >( windowWidth, windowHeight );
      ASSERT_TRUE( aIGU != nullptr );
      aIGU->addLayer( SolidLayer1 );
      aIGU->addLayer( m_GapLayer1 );
      aIGU->addLayer( shadeLayer );
      aIGU->addLayer( m_GapLayer2 );
      aIGU->addLayer( SolidLayer2 );

      /////////////////////////////////////////////////////////
      // System
      /////////////////////////////////////////////////////////
      m_TarcogSystem = make_shared< CTarcogSystem >( aIGU, Indoor, Outdoor );
      ASSERT_TRUE( m_TarcogSystem != nullptr );

    } catch( exception &e ) {
      cout << e.what() << endl;
      throw e;
    }
	};

public:
	shared_ptr< CTarIGUGapLayer > GetGap1() { return m_GapLayer1; };
  shared_ptr< CTarIGUGapLayer > GetGap2() { return m_GapLayer2; };

};

TEST_F( TestGapLayerInBetweenVentilation, VentilationFlow )
{
  try {
	  SCOPED_TRACE( "Begin Test: Test Ventilated Gap Layer - Intial Airflow" );
	  
	  shared_ptr< CTarIGUGapLayer > aLayer = nullptr;

    // Airflow iterations are set to 1e-4 and it cannot exceed that precision
	  
	  aLayer = GetGap1();
    ASSERT_TRUE( aLayer != nullptr );
    double gainEnergy = aLayer->getGainFlow();    
    EXPECT_NEAR( 32.414571203538848, gainEnergy, 1e-4 );

    aLayer = GetGap2();
    ASSERT_TRUE( aLayer != nullptr );
    gainEnergy = aLayer->getGainFlow();
	  EXPECT_NEAR( -32.414571203538848, gainEnergy, 1e-4 );


  } catch( exception &e ) {
    cout << e.what() << endl;
  }

}