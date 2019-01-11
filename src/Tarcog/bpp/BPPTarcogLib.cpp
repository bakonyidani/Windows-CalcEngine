#include <string>
#include <memory>
#include <iostream>
#include <boost/python.hpp>
#include "WCECommon.hpp"
#include "WCETarcog.hpp"

using namespace Tarcog;

class GlazingSystem
{
private:
  bool set;
  bool solved;
  //general inputs

  double pressure;
  double windowWidth;
  double windowHeight;
  //Outdoor Environment
  double airTemperature;
  double airSpeed;
  double tSky;
  double solarRadiation;
  std::shared_ptr<ISO15099::CEnvironment> OutdoorEnvironment;
  //Indoor Environment
  double roomTemperature;
  std::shared_ptr<ISO15099::CEnvironment> IndoorEnvironment;
  //Layers
  int numberOfLayers;
  //Solid Layers
  std::vector<double> solidLayerThickness;
  std::vector<double> solidLayerConductance;
  std::vector<double> emissivity1;
  std::vector<double> transmittance1;
  std::vector<double> emissivity2;
  std::vector<double> transmittance2;
  std::vector<std::shared_ptr<ISO15099::CIGUSolidLayer>> SolidLayers;
  //Air Gaps
  std::vector<double> gapThickness;
  std::vector<std::string> gasType;
  std::vector<Gases::CGas> Gases;
  std::vector<std::shared_ptr<ISO15099::CIGUGapLayer>> AirGaps;
  //IGU
  ISO15099::CIGU IGU;
  //Glazing System
  std::shared_ptr<ISO15099::CSingleSystem> System;
public:
  //The constructor
  GlazingSystem(){
    this->set = false;
    this->solved = false;
    this->pressure = 101325;//[Pa] - default value
  }//GlazingSystem

  //Get Temperatures
  boost::python::list getTemperatures(){
    boost::python::list array;
    auto Temperatures = this->System->getTemperatures();
    for (unsigned int i = 0; i < Temperatures.size(); i++){
      array.append( Temperatures[i] );
    }
    return array;
  }//getTemperatures

  //Get U value
  double getUValue(){
    return this->System->getUValue();
  }//getUValue

  //Initialize
  void initialize(){
    //outdoor
    this->OutdoorEnvironment = ISO15099::Environments::outdoor(this->airTemperature,this->airSpeed,this->solarRadiation,this->tSky, ISO15099::SkyModel::AllSpecified);
    this->OutdoorEnvironment->setHCoeffModel(ISO15099::BoundaryConditionsCoeffModel::CalculateH);
    //indoor
    this->IndoorEnvironment = ISO15099::Environments::indoor(this->roomTemperature);
    //IGU
    this->IGU = ISO15099::CIGU(this->windowWidth,this->windowHeight);
    for (int i=0; i<this->numberOfLayers; i++){
      //solid layer
      this->SolidLayers[i] = ISO15099::Layers::solid(this->solidLayerThickness[i],this->solidLayerConductance[i],this->emissivity1[i],this->transmittance1[i],this->emissivity2[i],this->transmittance2[i]);
      this->SolidLayers[i]->setSolarAbsorptance(0.094189159572);
      //add to the IGU
      this->IGU.addLayer(this->SolidLayers[i]);
      //air gap
      if (i<this->numberOfLayers-1){
        //set the proper Gas
        this->Gases[i] = Gases::CGas();
        if ( this->gasType[i].compare("Air") == 0 ){
          //do nothing - default is Air
        } else if (this->gasType[i].compare("Argon") == 0){
          this->Gases[i].addGasItem(1.0,Gases::GasDef::Argon);
        } else if (this->gasType[i].compare("Krypton") == 0){
          this->Gases[i].addGasItem(1.0,Gases::GasDef::Krypton);
        } else if (this->gasType[i].compare("Xenon") == 0){
          this->Gases[i].addGasItem(1.0,Gases::GasDef::Xenon);
        }
        //create the AirGap object
        this->AirGaps[i] = ISO15099::Layers::gap(this->gapThickness[i],this->Gases[i]);
        this->IGU.addLayer(this->AirGaps[i]);
      }//if (i<this->numberOfLayers-1){
    }//for (int i=0; i<this->numberOfLayers; i++){
    //System
    this->System = std::make_shared<ISO15099::CSingleSystem>(this->IGU,this->IndoorEnvironment,this->OutdoorEnvironment);
    this->set = true;
  }//Initialize

  //setSolidLayer
  void setAirGap(int lyr,double thickness,std::string gas){
    if (lyr <= this->numberOfLayers-1){
      lyr=lyr-1;//0 based indexing!
      this->gapThickness[lyr]=thickness;
      this->gasType[lyr]=gas;
    }
  }//setSize

  //Set Indoor Environment
  void setIndoorEnvironment(double roomTemperature){
    this->roomTemperature = roomTemperature;
  }//setIndoorEnvironment

  //Set the number of Layers
  void setNumberOfLayers(int numLayers){
    this->numberOfLayers = numLayers;
    //Solid Layers
    this->solidLayerThickness.resize(numLayers);
    this->solidLayerConductance.resize(numLayers);
    this->emissivity1.resize(numLayers);
    this->transmittance1.resize(numLayers);
    this->emissivity2.resize(numLayers);
    this->transmittance2.resize(numLayers);
    this->SolidLayers.resize(numLayers);
    //Air Gaps
    this->gapThickness.resize(numLayers);
    this->gasType.resize(numLayers);
    this->Gases.resize(numLayers);
    this->AirGaps.resize(numLayers);
  }//setNumberOfLayers

  //Set pressure
  void setPressure(double p){
    this->pressure = p;
  }//setPressure

  //Set Outdoor Environment
  void setOutdoorEnvironment(double airT, double airSpd, double solarRad, double tS){
    this->airTemperature = airT;
    this->airSpeed = airSpd;
    this->solarRadiation = solarRad;
    this->tSky = tS;
  }//setOutdoorEnvironment

  void setSize(double width, double height){
    this->windowWidth = width;
    this->windowHeight = height;
  }//setSize

  //setSolidLayer
  void setSolidLayer(int lyr,double thickness,double conductance,double eps1,double tau1,double eps2, double tau2){
    if (lyr <= this->numberOfLayers){
      lyr=lyr-1;//0 based indexing!
      this->solidLayerThickness[lyr]=thickness;
      this->solidLayerConductance[lyr]=conductance;
      this->emissivity1[lyr]=eps1;
      this->transmittance1[lyr]=tau1;
      this->emissivity2[lyr]=eps2;
      this->transmittance2[lyr]=tau2;
    }
  }//setSize

  void solve(){
    if (this->set){
      this->System->solve();
      this->solved = true;
    }
  }//solve

  //A test method
  void Test(){
    //outdoor
    this->OutdoorEnvironment = ISO15099::Environments::outdoor(this->airTemperature,this->airSpeed,this->solarRadiation,this->tSky, ISO15099::SkyModel::AllSpecified);
    this->OutdoorEnvironment->setHCoeffModel(ISO15099::BoundaryConditionsCoeffModel::CalculateH);
    //indoor
    this->IndoorEnvironment = ISO15099::Environments::indoor(this->roomTemperature);
    //solid layer
    auto solidLayerThickness = 0.003048;
    auto solidLayerConductance = 1.0;
    auto SolidLayer = ISO15099::Layers::solid(solidLayerThickness,solidLayerConductance);
    SolidLayer->setSolarAbsorptance(0.094189159572);
    //IGU
    auto TestIGU = ISO15099::CIGU(this->windowWidth,this->windowHeight);
    TestIGU.addLayer(SolidLayer);
    //System
    auto TestSystem = ISO15099::CSystem(TestIGU,this->IndoorEnvironment,this->OutdoorEnvironment);
    //Run
    auto Temperatures = TestSystem.getTemperatures(ISO15099::System::Uvalue);
    std::cout << "This is a test run of BPPGlazingSystem!" << std::endl;
    for (unsigned int i = 0; i < Temperatures.size(); i++)
    {
      std::cout << Temperatures[i] << std::endl;
    }
    //std::cout << "Temperatures: " << Temperatures << std::endl;
    return;
  }//void Test(){}

};//class GlazingSystem

//BOOST.python wrapper
BOOST_PYTHON_MODULE(BPPTarcogLib)
{
  using namespace boost::python;
  class_<GlazingSystem>("GlazingSystem", init<>())
    .def("getTemperatures", &GlazingSystem::getTemperatures)
    .def("getUValue", &GlazingSystem::getUValue)
    .def("initialize", &GlazingSystem::initialize)
    .def("setAirGap", &GlazingSystem::setAirGap)
    .def("setIndoorEnvironment", &GlazingSystem::setIndoorEnvironment)
    .def("setNumberOfLayers", &GlazingSystem::setNumberOfLayers)
    .def("setOutdoorEnvironment", &GlazingSystem::setOutdoorEnvironment)
    .def("setPressure", &GlazingSystem::setPressure)
    .def("setSize", &GlazingSystem::setSize)
    .def("setSolidLayer", &GlazingSystem::setSolidLayer)
    .def("solve", &GlazingSystem::solve)
    .def("Test", &GlazingSystem::Test);
}
