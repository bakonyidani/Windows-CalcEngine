
#include "BaseCellDescription.hpp"
// #include "BeamDirection.hpp"

namespace LayerOptics {

  CBaseCellDescription::CBaseCellDescription() {
    
  };

  double CBaseCellDescription::R_dir_dir( const FenestrationCommon::Side t_Side, 
    std::shared_ptr< const CBeamDirection > t_Direction ) {
    return 0; 
  };

}