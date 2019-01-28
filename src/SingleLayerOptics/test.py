import BPPSLOLib

#-------------------------------------------------------------------------------
print('Single Layer Optics - Test1: default data')
SLOSystem = BPPSLOLib.SLOSystem()
SLOSystem.setThickness(0.004)#thickness[m]
SLOSystem.setDefaultRadiationSpectra();
SLOSystem.setTestSpectralSampleData();
SLOSystem.initialize();
SLOSystem.solve();
results = SLOSystem.getBasicResults()
print(results)
print('So far so good...')
#-------------------------------------------------------------------------------
print('Single Layer Optics - Test2: spectrum input')
SLOSystem2 = BPPSLOLib.SLOSystem()
SLOSystem2.setThickness(0.004)#thickness[m]
wavelengths=[0.3000,0.3050,0.3100,0.3150,0.3200]
values=[0.0,3.4,15.6,41.1,71.2]
SLOSystem2.setRadiationSpectra(wavelengths,values);
SLOSystem2.setTestSpectralSampleData();
SLOSystem2.initialize();
SLOSystem2.solve();
results2 = SLOSystem2.getBasicResults()
print(results2)
print('So far so good...')
#-------------------------------------------------------------------------------
print('Single Layer Optics - Test3: spectrum and spectral data input')
SLOSystem3 = BPPSLOLib.SLOSystem()
SLOSystem3.setThickness(0.004)#thickness[m]
wavelengths=[0.3000,0.3050,0.3100,0.3150,0.3200]
values=[0.0,3.4,15.6,41.1,71.2]
T=[0,0.1,0.2,0.3,0.4]
Rf=[0,0.01,0.02,0.03,0.04]
Rb=[0,0.01,0.02,0.03,0.04]
SLOSystem3.setRadiationSpectra(wavelengths,values);
SLOSystem3.setSpectralSampleData(wavelengths,T,Rf,Rb);
SLOSystem3.setMaterialType('Monolithic');
SLOSystem3.setWavelengthRange('Solar');
SLOSystem3.initialize();
SLOSystem3.solve();
results3 = SLOSystem3.getBasicResults()
print(results3)
print('So far so good...')
