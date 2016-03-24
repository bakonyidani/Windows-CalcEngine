#include <assert.h>
#include <memory>

#include "PerforatedCellDescription.hpp"
#include "BeamDirection.hpp"
#include "MathFunctions.hpp"

using namespace std;
using namespace FenestrationCommon;

namespace LayerOptics {

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // CPerforatedCellDescription
  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  CPerforatedCellDescription::CPerforatedCellDescription( const double t_x, const double t_y, const double t_Thickness ) :
    m_x( t_x ), m_y( t_y ), m_Thickness( t_Thickness ) {
  
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // CCircularCellDescription
  //////////////////////////////////////////////////////////////////////////////////////////////////

  CCircularCellDescription::CCircularCellDescription( const double t_x, const double t_y, const double t_Thickness, 
      const double t_Radius ) : CPerforatedCellDescription( t_x, t_y, t_Thickness ), m_Radius( t_Radius ) {
    
  };

  double CCircularCellDescription::T_dir_dir( const FenestrationCommon::Side, 
    shared_ptr< const CBeamDirection > t_Direction ) {
		return visibleAhole( t_Direction ) / visibleAcell( t_Direction );
  };

  double CCircularCellDescription::visibleAhole( shared_ptr< const CBeamDirection > t_Direction ) const {
    double A1( 0 ), A2( 0 );
		double AngleLimit( 0 );
    double aHole( 0 );

		AngleLimit = atan( 2 * m_Radius / m_Thickness );

    double aTheta = radians( t_Direction->theta() );

		if( ( aTheta < 0 ) || ( aTheta > AngleLimit ) ) {
			aHole = 0;
		}
		else {
			A1 = M_PI / 2 * m_Radius * m_Radius * cos( aTheta );
			A2 = M_PI / 2 * ( m_Radius * m_Radius * cos( aTheta ) - m_Radius * 
        ( m_Thickness ) * sin( aTheta ) );

			aHole = A1 + A2;
		}

		return aHole;  
  };

	double CCircularCellDescription::visibleAcell( shared_ptr< const CBeamDirection > t_Direction ) const {
    double aTheta = radians( t_Direction->theta() );
    return ( m_x * m_y ) * cos( aTheta );
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // CRectangularCellDescription
  //////////////////////////////////////////////////////////////////////////////////////////////////

  CRectangularCellDescription::CRectangularCellDescription( const double t_x, const double t_y, const double t_Thickness, 
    const double t_XHole, const double t_YHole ) : CPerforatedCellDescription( t_x, t_y, t_Thickness ), 
    m_XHole( t_XHole ), m_YHole( t_YHole ) {
    
  };

  double CRectangularCellDescription::T_dir_dir( const FenestrationCommon::Side, 
    std::shared_ptr< const CBeamDirection > t_Direction ) {
		return TransmittanceH( t_Direction ) * TransmittanceV( t_Direction );
  };

  double CRectangularCellDescription::TransmittanceV( shared_ptr< const CBeamDirection > t_Direction ) const {
    double Psi( 0 );
		double lowerLimit( 0 ), upperLimit( 0 );
		double Transmittance( 0 );

		lowerLimit = -( atan( m_YHole / m_Thickness ) );
		upperLimit = -lowerLimit;
		
		Psi = -t_Direction->profileAngle();
    Psi = radians( Psi );

		if( ( Psi <= lowerLimit ) || ( Psi >= upperLimit ) ) {
			return 0.0;
		}
		else {
			Transmittance = ( ( m_YHole / m_y ) - fabs( m_Thickness / m_y * tan( Psi ) ) );
			if (Transmittance < 0) Transmittance = 0;
			return Transmittance;
		}  
  };

	double CRectangularCellDescription::TransmittanceH( shared_ptr< const CBeamDirection > t_Direction ) const {
    double Eta( 0 );
		double lowerLimit( 0 ), upperLimit( 0 );
		double Transmittance( 0 );

		lowerLimit = -( atan( m_XHole / m_Thickness ) );
		upperLimit = -lowerLimit;

    double Phi = radians( t_Direction->phi() );
    double Theta = radians( t_Direction->theta() );
		
		Eta = atan( cos( Phi ) * tan( Theta ) );

		if((Eta <= lowerLimit) || (Eta >= upperLimit)) {
			return 0.0;
		}
		else {
			Transmittance = ( ( m_XHole / m_x ) - fabs( m_Thickness / m_x * tan(Eta) ) );
			if ( Transmittance < 0 ) Transmittance = 0;
			return Transmittance;
		}  
  };

}