#ifndef ANGULARSPECTRALSAMPLE_H
#define ANGULARSPECTRALSAMPLE_H

#include <memory>
#include <vector>

namespace FenestrationCommon {

  enum class SpecularMaterialType;
  enum class Side;
  enum class Property;

}

namespace SpectralAveraging {

  class CSpectralSampleData;
  class CSpectralProperties;
  class CSpectralSample;
  // enum class SampleProperty;
  
  // Angular properties for each wavelength of measured data
  class CAngularSpectralProperties {
  public:
    CAngularSpectralProperties( std::shared_ptr< CSpectralSample > t_SpectralSample, const double t_Angle,
      const FenestrationCommon::SpecularMaterialType t_Type, const double t_Thickness );

    double angle() const;
    std::shared_ptr< CSpectralSampleData > properties() const;

  private:
    void calculateAngularProperties( std::shared_ptr< CSpectralSample > t_SpectralSample, 
      FenestrationCommon::SpecularMaterialType t_Type );

    double m_Angle;
    double m_Thickness;
    std::shared_ptr< CSpectralSampleData > m_AngularData;
  };

  // Data for spectral sample under certain angle
  class CSpectralSampleAngle {
  public:
    CSpectralSampleAngle( std::shared_ptr< CSpectralSample > t_Sample, const double t_Angle );

    double angle() const;
    std::shared_ptr< CSpectralSample > sample() const;

  private:
    std::shared_ptr< CSpectralSample > m_Sample;
    double m_Angle;
  };

  class CAngularSpectralSample {
  public:
    CAngularSpectralSample( std::shared_ptr< CSpectralSample > t_SpectralSample, const double t_Thickness,
      const FenestrationCommon::SpecularMaterialType t_Type );

    // Get averaged property over the wavelength
    double getProperty( double const minLambda, double const maxLambda, 
      const FenestrationCommon::Property t_Property, const FenestrationCommon::Side t_Side, const double t_Angle );

    // Get property at each wavelength
    std::shared_ptr< std::vector< double > > getWavelengthsProperty( double const minLambda, double const maxLambda, 
      const FenestrationCommon::Property t_Property, const FenestrationCommon::Side t_Side, const double t_Angle );

    std::shared_ptr< std::vector< double > > getBandWavelengths() const;

  private:
    // Finds spectral sample or creates new one if sample is not already created
    std::shared_ptr< CSpectralSample > findSpectralSample( const double t_Angle );
    std::vector< std::shared_ptr< CSpectralSampleAngle > > m_SpectralProperties;
    std::shared_ptr< CSpectralSample > m_SpectralSampleZero; // spectral sample as zero degrees
    double m_Thickness;
    FenestrationCommon::SpecularMaterialType m_Type;

  };

}

#endif