#include <memory>
#include <stdexcept>
#include <gtest\gtest.h>

#include "TarOutdoorEnvironment.hpp"
#include "TarIndoorEnvironment.hpp"
#include "TarIGUSolidLayer.hpp"
#include "TarIGU.hpp"
#include "TarcogSystem.hpp"
#include "TarSurface.hpp"

using namespace Tarcog;
using namespace std;

class TestSingleClear : public testing::Test
{

private:
  shared_ptr< CTarIGUSolidLayer > m_SolidLayer;
  shared_ptr< CTarcogSystem > m_TarcogSystem;

protected:
	virtual void SetUp()
	{    
    try {
      /////////////////////////////////////////////////////////
      // Outdoor
      /////////////////////////////////////////////////////////
      double airTemperature = 300; // Kelvins
      double pressure = 101325; // Pascals
      double airSpeed = 5.5; // meters per second
      AirHorizontalDirection airDirection = AirHorizontalDirection::Windward;
      double tSky = 270; // Kelvins

      shared_ptr< CTarOutdoorEnvironment > Outdoor = 
        make_shared< CTarOutdoorEnvironment >( airTemperature, pressure, airSpeed, airDirection );
      ASSERT_TRUE( Outdoor != nullptr );
      Outdoor->setSkyTemperature( tSky );
      Outdoor->setHCoeffModel( BoundaryConditionsCoeffModel::CalculateH );
      Outdoor->setSkyModel( SkyModel::AllSpecified );

      /////////////////////////////////////////////////////////
      // Indoor
      /////////////////////////////////////////////////////////

      double roomTemperature = 294.15;
      double roomAirSpeed = 0;

      shared_ptr< CTarIndoorEnvironment > Indoor = 
        make_shared< CTarIndoorEnvironment > ( roomTemperature, pressure, roomAirSpeed, airDirection );
      ASSERT_TRUE( Indoor != nullptr );

      /////////////////////////////////////////////////////////
      // IGU
      /////////////////////////////////////////////////////////
      double solidLayerThickness = 0.003048; // [m]
      double solidLayerConductance = 1;

      m_SolidLayer = make_shared< CTarIGUSolidLayer > ( solidLayerThickness, solidLayerConductance );
      ASSERT_TRUE( m_SolidLayer != nullptr );

      double windowWidth = 1;
      double windowHeight = 1;
      shared_ptr< CTarIGU > aIGU = make_shared< CTarIGU >( windowWidth, windowHeight );
      ASSERT_TRUE( aIGU != nullptr );
      aIGU->addLayer( m_SolidLayer );

      /////////////////////////////////////////////////////////
      // System
      /////////////////////////////////////////////////////////
      m_TarcogSystem = make_shared< CTarcogSystem >( aIGU, Indoor, Outdoor );
      ASSERT_TRUE( m_TarcogSystem != nullptr );

      m_TarcogSystem->solve();

    } catch( exception &e ) {
      cout << e.what() << endl;
      throw e;
    }
	};

public:
	shared_ptr< CTarcogSystem > GetSystem() { return m_TarcogSystem; };
  shared_ptr< CTarIGUSolidLayer > GetSolidLayer() { return m_SolidLayer; };

};

TEST_F( TestSingleClear, Test1 )
{
  try {
	  SCOPED_TRACE( "Begin Test: Single Clear - U-value" );
	  
	  shared_ptr< CTarcogSystem > aSystem = nullptr;
    shared_ptr< CTarIGUSolidLayer > aLayer = nullptr;
	  
	  aSystem = GetSystem();
    ASSERT_TRUE( aSystem != nullptr );
    aSystem->solve();

    aLayer = GetSolidLayer();

    ASSERT_TRUE( aLayer != nullptr );

    shared_ptr< CTarSurface > aSurface = aLayer->getSurface( SurfacePosition::Front );
    ASSERT_TRUE( aSurface != nullptr );

    double Temperature = aSurface->getTemperature();
    double Radiosity = aSurface->J();

    EXPECT_NEAR( 297.207035, Temperature, 1e-5 );
    EXPECT_NEAR( 432.444546, Radiosity, 1e-5 );

    aSurface = aLayer->getSurface( SurfacePosition::Back );
    ASSERT_TRUE( aSurface != nullptr );

    Temperature = aSurface->getTemperature();
    Radiosity = aSurface->J();

    EXPECT_NEAR( 297.14470, Temperature, 1e-5 );
    EXPECT_NEAR( 439.201749, Radiosity, 1e-5 );

  } catch( exception &e ) {
    cout << e.what() << endl;
  }

}