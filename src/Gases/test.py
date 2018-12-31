import BPPGasLib
BPPGasLib.test()

gas = BPPGasLib.BPPGas()
gas.setPureGas('Argon')
gas.setTemperatureAndPressure(293.15,101325)
gas.getSimpleGasProperties()
gas.printProperties()
prop = gas.returnGasPropertiesList()
print(prop)

