#ifndef BASETARCOGLAYER_H
#define BASETARCOGLAYER_H

#include "LayerInterfaces.hpp"

#include <memory>

namespace Tarcog {

  class CTarSurface;
  enum class SurfacePosition;

  class CBaseTarcogLayer : public CLayerGeometry, public CLayerHeatFlow,
    public std::enable_shared_from_this< CBaseTarcogLayer > {
  public:
    CBaseTarcogLayer();
    
    std::shared_ptr< CBaseTarcogLayer > getPreviousLayer() const;
    std::shared_ptr< CBaseTarcogLayer > getNextLayer() const;

    virtual void connectToBackSide( std::shared_ptr< CBaseTarcogLayer > t_Layer );

    void tearDownConnections();

  protected:
    virtual void calculateRadiationState();
    virtual void calculateConvectionConductionState();

    std::shared_ptr< CBaseTarcogLayer > m_PreviousLayer;
    std::shared_ptr< CBaseTarcogLayer > m_NextLayer;

  };

}

#endif