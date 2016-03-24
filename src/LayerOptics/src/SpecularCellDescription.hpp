#ifndef SPECULARCELLDESCRIPTION_H
#define SPECULARCELLDESCRIPTION_H

#include "BaseCellDescription.hpp"

namespace FenestrationCommon {

  enum class Side;
  enum class SpecularMaterialType;

}

namespace LayerOptics {

  class CSpecularCellDescription : public CBaseCellDescription {
  public:
    CSpecularCellDescription();
    
    double T_dir_dir( const FenestrationCommon::Side t_Side, std::shared_ptr< const CBeamDirection > t_Direction );
    double Rspecular( const FenestrationCommon::Side t_Side, std::shared_ptr< const CBeamDirection > t_Direction );

  };

}

#endif