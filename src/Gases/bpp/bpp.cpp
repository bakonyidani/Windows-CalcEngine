#include <string>
#include <memory>
#include <iostream>
#include "WCEGases.hpp"
#include <boost/python.hpp>
using namespace Gases;

void test()
{
	CGas myGas;
	myGas.setTemperatureAndPressure(293.15, 101325);
	const GasProperties & myGasProperties = myGas.getSimpleGasProperties();
	std::cout << "This is a test of the CGas class!" << std::endl;
	std::cout << "Molecular weight: " << myGasProperties.m_MolecularWeight << std::endl;
	return;
}

class BPPGas
{
	private:
		CGas thisGas;
		GasProperties thisGasProperties;
		bool gasTypeSet;
		bool gasPropertiesCalculated;
                bool temperatureSet;
	public:
		BPPGas(){
		  this->gasTypeSet = false;
                  this->temperatureSet = false;
		  this->gasPropertiesCalculated = false;
		}//BPPGas

		void setPureGas(std::string gasTypeStr){
		  if ( gasTypeStr.compare("Air") == 0 ){
		       this->thisGas = CGas();
           this->gasTypeSet = true;
		  } else if (gasTypeStr.compare("Argon") == 0){
		       this->thisGas = CGas();
		       this->thisGas.addGasItem(1.0,GasDef::Argon);
           this->gasTypeSet = true;
		  } else if (gasTypeStr.compare("Krypton") == 0){
		       this->thisGas = CGas();
		       this->thisGas.addGasItem(1.0,GasDef::Krypton);
		       this->gasTypeSet = true;
      } else if (gasTypeStr.compare("Xenon") == 0){
		       this->thisGas = CGas();
		       this->thisGas.addGasItem(1.0,GasDef::Xenon);
	         this->gasTypeSet = true;
      }//if (...)
		}//setPureGas

		void setTemperatureAndPressure(double teta, double p){
		  if(this->gasTypeSet){ this->thisGas.setTemperatureAndPressure(teta,p); }
		}//setTemperatureAndPressure

		void getSimpleGasProperties(){
		  if(this->gasTypeSet){
		    this->thisGasProperties = this->thisGas.getSimpleGasProperties();
		    this->gasPropertiesCalculated = true;
		  }
		}//getSimpleGasProperties

		void getGasProperties(){
		  if(this->gasTypeSet){
		    this->thisGasProperties = this->thisGas.getGasProperties();
		    this->gasPropertiesCalculated = true;
                  }
		}//getGasProperties

		void printProperties(){
		  if((this->gasTypeSet) && (this->gasPropertiesCalculated)){
                    std::cout << "Molecular Weight: " << this->thisGasProperties.m_MolecularWeight << std::endl;
		    std::cout << "Thermal conductivity: " << this->thisGasProperties.m_ThermalConductivity << std::endl;
	            std::cout << "Viscosity: " << this->thisGasProperties.m_Viscosity << std::endl;
	            std::cout << "Specific Heat: " << this->thisGasProperties.m_SpecificHeat << std::endl;
	            std::cout << "Density: " << this->thisGasProperties.m_Density << std::endl;
	            std::cout << "Alpha: " << this->thisGasProperties.m_Alpha << std::endl;
		    std::cout << "Prandtl Number: " << this->thisGasProperties.m_PrandlNumber << std::endl;
                  }
                }//printProperties

		boost::python::list returnGasPropertiesList(){
		  boost::python::list array;
                  array.append( this->thisGasProperties.m_MolecularWeight );
                  array.append( this->thisGasProperties.m_ThermalConductivity );
                  array.append( this->thisGasProperties.m_Viscosity );
                  array.append( this->thisGasProperties.m_SpecificHeat );
                  array.append( this->thisGasProperties.m_Density );
                  array.append( this->thisGasProperties.m_Alpha );
                  array.append( this->thisGasProperties.m_PrandlNumber );
	          return array;
		}//retunGasPropertiesList

};//class BPPGas

//Boost.python wrapper
BOOST_PYTHON_MODULE(BPPGasLib)
{
	using namespace boost::python;
	def("test",test);
	class_<BPPGas>("BPPGas", init<>())
	  .def("setPureGas", &BPPGas::setPureGas)
	  .def("setTemperatureAndPressure", &BPPGas::setTemperatureAndPressure)
	  .def("getSimpleGasProperties", &BPPGas::getSimpleGasProperties)
	  .def("getGasProperties", &BPPGas::getGasProperties)
	  .def("returnGasPropertiesList", &BPPGas::returnGasPropertiesList)
	  .def("printProperties", &BPPGas::printProperties);
}
