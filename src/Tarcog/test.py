import BPPTarcogLib

#-------------------------------------------------------------------------------
print('Single Glass:')
GlazingSystem = BPPTarcogLib.GlazingSystem()
GlazingSystem.setPressure(101325)#atmospheric pressure [Pa], default is 101325
GlazingSystem.setSize(1,1)#width[m],height[m]
GlazingSystem.setOutdoorEnvironment(273.15,5.5,0,273.15)#airTemperature[K],windSpeed[m/s],solarRaidation[W/m2],tSky[K]
GlazingSystem.setIndoorEnvironment(293.15)#roomTemperature[K]
#Glazing system
GlazingSystem.setNumberOfLayers(1)
GlazingSystem.setSolidLayer(1,0.004,1,0.84,0,0.15,0)#layer,thickness[m],conductivity[W/mK],eps1[-],tau1[-],eps2[-],tau2[-]
#Solve
GlazingSystem.initialize()#create the CSystem object form all the inputs
GlazingSystem.solve()
#get some results
print('Temperatures: ',GlazingSystem.getTemperatures())#returns a list
print('U Value: ',GlazingSystem.getUValue())#returns a double
#-------------------------------------------------------------------------------
print('Double Glass:')
GS2 = BPPTarcogLib.GlazingSystem()
GS2.setSize(1,1)
GS2.setOutdoorEnvironment(273.15,5.5,0,273.15)#airTemperature[K],windSpeed[m/s],solarRaidation[W/m2],tSky[K]
GS2.setIndoorEnvironment(293.15)#roomTemperature[K]
#Glazing system
GS2.setNumberOfLayers(2)
GS2.setSolidLayer(1,0.004,1,0.84,0,0.84,0)#layer,thickness[m],conductivity[W/mK],eps1[-],tau1[-],eps2[-],tau2[-]
GS2.setAirGap(1,0.024,'Argon')#Layer,thickness[m],gas{'Air','Argon'}
GS2.setSolidLayer(2,0.004,1,0.034,0,0.84,0)#layer,thickness[m],conductivity[W/mK],eps1[-],tau1[-],eps2[-],tau2[-]
#Solve
GS2.initialize()
GS2.solve()
#get some results
print('Temperatures: ',GS2.getTemperatures())#returns a list
print('U Value: ',GS2.getUValue())#returns a double
#-------------------------------------------------------------------------------
print('Binglibong!')
