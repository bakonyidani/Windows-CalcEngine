#include <memory>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include "WCEGases.hpp"

using namespace Gases;
int main(int argc, char *argv[])
{
#ifdef ENABLE_GTEST_DEBUG_MODE
  ::testing::GTEST_FLAG(break_on_failure) = true;
  ::testing::GTEST_FLAG(catch_exceptions) = false;
#endif
  ::testing::InitGoogleTest(&argc, argv);
  
  //xx
  //std::cout << "Binglibong!" << std::endl;
  std::cout << "This is a test of the CGas class!" << std::endl; 
  CGas myGas;
  myGas.setTemperatureAndPressure( 300, 101325);
  const GasProperties & myGasProperties = myGas.getSimpleGasProperties();
  std::cout << myGasProperties.m_MolecularWeight << std::endl;
  //xx
  
  return 0; //RUN_ALL_TESTS();
  
}
