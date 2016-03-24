#ifndef BEAMDIRECTION_H
#define BEAMDIRECTION_H

#include <memory>

namespace LayerOptics {

  // Hold spherical point data for beam. Phi angle is measured in clockwise direction starting from positive direction
  // of x-axis. Theta angle is measured starting from indicent direction (z-axis) towards x0y plane. Limits of
  // Phi are 0 to 360 degrees and limits of Theta are 0 to 90 degrees
  class CBeamDirection {
  public:
    CBeamDirection( const double t_Theta, const double t_Phi );

    double theta() const;
    double phi() const;
    double profileAngle() const;

    CBeamDirection& operator=( const CBeamDirection& t_SphericalPoint );

    double Altitude() const;
    double Azimuth() const;

  private:
    const double m_Theta;
    const double m_Phi;
    double m_ProfileAngle;
  };

}

#endif