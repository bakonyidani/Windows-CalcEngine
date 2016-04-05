#include <stdexcept>
#include <assert.h>

#include "MeasuredSampleData.hpp"
#include "Series.hpp"

using namespace std;
using namespace FenestrationCommon;

namespace SpectralAveraging {

  ////////////////////////////////////////////////////////////////////////////
  ////     CSpectralSampleData
  ////////////////////////////////////////////////////////////////////////////

  CSpectralSampleData::CSpectralSampleData() : 
    m_Transmittances( make_shared< CSeries >() ), m_ReflectancesFront( make_shared< CSeries >() ),
    m_ReflectancesBack( make_shared< CSeries >() ), m_AbsorptancesFront( make_shared< CSeries >()), 
    m_AbsorptancesBack( make_shared< CSeries >() ), m_Flipped( false ), m_absCalculated( false ) {

  }

  void CSpectralSampleData::addRecord( double t_Wavelength, double t_Transmittance, double t_ReflectanceFront, 
    double t_ReflectanceBack ) {
    m_Transmittances->addProperty( t_Wavelength, t_Transmittance );
    m_ReflectancesFront->addProperty( t_Wavelength, t_ReflectanceFront );
    m_ReflectancesBack->addProperty( t_Wavelength, t_ReflectanceBack );
    reset();
  }

  shared_ptr< CSeries > CSpectralSampleData::properties( SampleData t_Property ) {
    calculateProperties();
    shared_ptr< CSeries > aProperties = nullptr;
    switch ( t_Property ) {
    case SampleData::T:
      aProperties = m_Transmittances;
      break;
    case SampleData::Rf:
      aProperties = m_Flipped ? m_ReflectancesBack : m_ReflectancesFront;
      break;
    case SampleData::Rb:
      aProperties = m_Flipped ? m_ReflectancesFront : m_ReflectancesBack;
      break;
    case SampleData::AbsF:
      aProperties = m_AbsorptancesFront;
      break;
    case SampleData::AbsB:
      aProperties = m_AbsorptancesBack;
      break;
    default:
      throw runtime_error("Incorrect selection of sample property.");
      break;
    }
    return aProperties;
  };

  shared_ptr< vector< double > > CSpectralSampleData::getWavelengths() {
    return m_Transmittances->getXArray();
  };

  // Interpolate current sample data to new wavelengths set
  void CSpectralSampleData::interpolate( shared_ptr< vector< double > > t_Wavelengths ) {
    m_Transmittances = m_Transmittances->interpolate( t_Wavelengths );
    m_ReflectancesFront = m_ReflectancesFront->interpolate( t_Wavelengths );
    m_ReflectancesBack = m_ReflectancesBack->interpolate( t_Wavelengths );
    m_AbsorptancesFront = m_AbsorptancesFront->interpolate( t_Wavelengths );
    m_AbsorptancesBack = m_AbsorptancesBack->interpolate( t_Wavelengths );
  };

  bool CSpectralSampleData::Flipped() const {
    return m_Flipped;
  };

  void CSpectralSampleData::Filpped( bool const t_Flipped ) {
    m_Flipped = t_Flipped;
  };

  void CSpectralSampleData::reset() {
    m_absCalculated = false;
  }

  void CSpectralSampleData::calculateProperties() {
    if( !m_absCalculated ) {
      shared_ptr< CSeries > reflectancesFront = nullptr;
      shared_ptr< CSeries > reflectancesBack = nullptr;
      if( m_Flipped ) {
        reflectancesFront = m_ReflectancesBack;
        reflectancesBack = m_ReflectancesFront;
      } else {
        reflectancesFront = m_ReflectancesFront;
        reflectancesBack = m_ReflectancesBack;
      }

      m_AbsorptancesFront->clear();
      m_AbsorptancesBack->clear();

      size_t size = m_Transmittances->size();

      for( size_t i = 0; i < size; ++i ) {
        double wv = (*m_Transmittances)[i]->x();
        double value = 1 - (*m_Transmittances)[i]->value() - (*reflectancesFront)[i]->value();
        m_AbsorptancesFront->addProperty( wv, value );
        value = 1 - (*m_Transmittances)[i]->value() - (*reflectancesBack)[i]->value();
        m_AbsorptancesBack->addProperty( wv, value );
      }
      m_absCalculated = true;
    }
    
  };
  
}