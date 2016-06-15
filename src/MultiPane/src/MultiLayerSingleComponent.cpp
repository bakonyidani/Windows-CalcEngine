#include <assert.h>

#include "MultiLayerSingleComponent.hpp"
#include "MultiLayerInterRefSingleComponent.hpp"
#include "EquivalentLayerSingleComponent.hpp"

using namespace std;
using namespace FenestrationCommon;

namespace MultiPane {

  CMultiLayerSingleComponent::CMultiLayerSingleComponent( const double t_Tf, const double t_Rf, const double t_Tb, const double t_Rb ) {
    m_Inter = make_shared< CInterRefSingleComponent >( t_Tf, t_Rf, t_Tb, t_Rb );
    m_Equivalent = make_shared< CEquivalentLayerSingleComponent >( t_Tf, t_Rf, t_Tb, t_Rb );
  }

  void CMultiLayerSingleComponent::addLayer( const double t_Tf, const double t_Rf, const double t_Tb, 
    const double t_Rb, Side t_Side ) {
    m_Inter->addLayer( t_Tf, t_Rf, t_Tb, t_Rb, t_Side );
    m_Equivalent->addLayer( t_Tf, t_Rf, t_Tb, t_Rb, t_Side );
  }

  double CMultiLayerSingleComponent::getProperty( const Property t_Property, const Side t_Side ) const {
    return m_Equivalent->getProperty( t_Property, t_Side );
  }

  double CMultiLayerSingleComponent::getLayerAbsorptance( const size_t Index, const Side t_Side ) {
    return m_Inter->getLayerAbsorptance( Index, t_Side );
  }

}