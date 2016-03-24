#ifndef BSDFPHIANGLES_H
#define BSDFPHIANGLES_H

#include <vector>
#include <memory>

namespace LayerOptics {

  class CBSDFPhiAngles {
  public:
    CBSDFPhiAngles( const size_t t_NumOfPhis );

    std::shared_ptr< std::vector< double > > phiAngles() const;

  private:
    void createPhis( const size_t t_NumOfPhis );

    std::shared_ptr< std::vector< double > > m_PhiAngles;
  };

}

#endif