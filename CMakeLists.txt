cmake_minimum_required( VERSION 3.13.2 )

set( target_name Windows-CalcEngine )
set( CMAKE_CXX_STANDARD 11 )
set( BOOST_ROOT $ENV{HOME}/anaconda3/envs/artheseus )
set( BOOST_INCLUDEDIR $ENV{HOME}/anaconda3/envs/artheseus/include )
set( BOOST_LIBRARYDIR $ENV{HOME}/anaconda3/envs/artheseus/lib/boost )
set( BOOST_NO_SYSTEM_PATHS ON )

project( ${target_name} )

include( cmake/WCEProjectMacros.cmake )
include( cmake/WCEInternalUtils.cmake )
include( cmake/WCECompilerFlags.cmake )

# google test will not be created by this project if this is not main project. Main project is expected to handle google test.
get_directory_property(hasParent PARENT_DIRECTORY)

if(hasParent)
	#message("xx CMakeLists.txt - hasParent true")
  	set( BUILD_WCE_TESTING OFF )
 	set( DOWNLOAD_GTEST OFF )
  	if( BUILD_TESTING STREQUAL ON ) # EnergyPlus testing is ON
    		set( BUILD_WCE_TESTING ON )
  	endif()
  	set( SINGLE_PROJECT ON )
else()
	#message("xx CMakeLists.txt - hasParent false")
	option( BUILD_WCE_TESTING "Build testing targets" OFF )
	option( SINGLE_PROJECT "Build windows library as single project" OFF )
	set( DOWNLOAD_GTEST OFF )
endif()

if( DOWNLOAD_GTEST STREQUAL ON ) # Do not need gtest since it will be processed by E+
	message("xx CMakeLists.txt - download gtest")
	# include(CMakeLists-GTest.txt)
	configure_file(CMakeLists.txt.in ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
	execute_process(COMMAND ${CMAKE_COMMAND} --build .
  		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
  		
  	# Prevent GoogleTest from overriding our compiler/linker options
	# when building with Visual Studio
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
 
	# Add googletest directly to our build. This adds
	# the following targets: gtest, gtest_main, gmock
	# and gmock_main
	add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
    	${CMAKE_BINARY_DIR}/googletest-build)
 
	# Now simply link your own targets against gtest, gmock,
	# etc. as appropriate:
  		
    include_directories( ${CMAKE_BINARY_DIR}/googletest-src/include )
endif ()

# foreach( _variableName ${SOURCES})
#   message( STATUS "${_variableName}" )
# endforeach()

#Boost.python stuff
find_package (PythonInterp)
if (PYTHONINTERP_FOUND)
  if (UNIX AND NOT APPLE)
    if (PYTHON_VERSION_MAJOR EQUAL 3)
      set(Boost_USE_STATIC_LIBS OFF)
      set(Boost_USE_MULTITHREADED ON)
      set(Boost_USE_STATIC_RUNTIME OFF)
      find_package(Boost REQUIRED COMPONENTS system python${PYTHON_VERSION_SUFFIX})
      find_package(PythonInterp 3)
      find_package(PythonLibs 3 REQUIRED)
    endif()
  endif()
endif()
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

#Debugging messages
message("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx")
message("xx CMakeLists.txt - project: ${PROJECT_NAME}")
message("xx CMakeLists.txt - Binary Tree path: ${PROJECT_BINARY_DIR}")
message("xx CMakeLists.txt - Project Source Tree path: ${PROJECT_SOURCE_DIR}")
message("xx CMakeLists.txt - BUILD_WCE_TESTING: ${BUILD_WCE_TESTING}")
message("xx CMakeLists.txt - SINGLE_PROJECT: ${SINGLE_PROJECT}")
message("xx CMakeLists.txt - PythonInterp: ${PythonInterp}")
message("xx CMakeLists.txt - PYTHON_VERSION_MAJOR: ${PYTHON_VERSION_MAJOR}")
message("xx CMakeLists.txt - PYTHON_VERSION_MINOR: ${PYTHON_VERSION_MINOR}")
message("xx CMakeLists.txt - PYTHON_LIBRARIES: ${PYTHON_LIBRARIES}")
message("xx CMakeLists.txt - PYTHON_EXECUTABLE: ${PYTHON_EXECUTABLE}")
message("xx CMakeLists.txt - PYTHON_INCLUDE_DIRS: ${PYTHON_INCLUDE_DIRS}")
message("xx CMakeLists.txt - Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message("xx CMakeLists.txt - Boost_LIBRARIES: ${Boost_LIBRARIES}")
message("xx CMakeLists.txt - Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message("xx CMakeLists.txt - Boost_USE_STATIC_RUNTIME: ${Boost_USE_STATIC_RUNTIME}")
message("xx CMakeLists.txt - Boost_USE_STATIC_LIBS: ${Boost_USE_STATIC_LIBS}")
message("xx CMakeLists.txt - PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
if( NOT ${SINGLE_PROJECT} )
  if( NOT BUILD_WCE_TESTING )
  	include_directories( src/Common/include ) 
  	include_directories( src/Chromogenics/include )
  	include_directories( src/Gases/include )
  	include_directories( src/Tarcog/include )  	
  	include_directories( src/SpectralAveraging/include )
  	include_directories( src/Viewer/include )
  	include_directories( src/SingleLayerOptics/include )
  	include_directories( src/MultiLayerOptics/include )
  endif()#if( NOT BUILD_WCE_TESTING)
  add_subdirectory( src )
else()
  message("xx CMakeLists.txt - SINGLE PROJECT")
  message("xx CMakeLists.txt - adding files")
  file( GLOB SOURCES_CPP "src/Common/src/*.cpp" )
  file( GLOB SOURCES_HPP "src/Common/src/*.hpp" )
  LIST(APPEND SOURCES ${SOURCES_HPP} ${SOURCES_CPP})
  
  file( GLOB SOURCES_CPP "src/Gases/src/*.cpp" )
  file( GLOB SOURCES_HPP "src/Gases/src/*.hpp" )
  LIST(APPEND SOURCES ${SOURCES_HPP} ${SOURCES_CPP})
  
  file( GLOB SOURCES_CPP "src/Tarcog/src/*.cpp" )
  file( GLOB SOURCES_HPP "src/Tarcog/src/*.hpp" )
  LIST(APPEND SOURCES ${SOURCES_HPP} ${SOURCES_CPP})
  
  file( GLOB SOURCES_CPP "src/SpectralAveraging/src/*.cpp" )
  file( GLOB SOURCES_HPP "src/SpectralAveraging/src/*.hpp" )
  LIST(APPEND SOURCES ${SOURCES_HPP} ${SOURCES_CPP})
  
  file( GLOB SOURCES_CPP "src/Viewer/src/*.cpp" )
  file( GLOB SOURCES_HPP "src/Viewer/src/*.hpp" )
  LIST(APPEND SOURCES ${SOURCES_HPP} ${SOURCES_CPP})
  
  file( GLOB SOURCES_CPP "src/SingleLayerOptics/src/*.cpp" )
  file( GLOB SOURCES_HPP "src/SingleLayerOptics/src/*.hpp" )
  LIST(APPEND SOURCES ${SOURCES_HPP} ${SOURCES_CPP})
  
  file( GLOB SOURCES_CPP "src/MultiLayerOptics/src/*.cpp" )
  file( GLOB SOURCES_HPP "src/MultiLayerOptics/src/*.hpp" )
  LIST(APPEND SOURCES ${SOURCES_HPP} ${SOURCES_CPP})
  
  file( GLOB SOURCES_CPP "src/Chromogenics/src/*.cpp" )
  file( GLOB SOURCES_HPP "src/Chromogenics/src/*.hpp" )
  LIST(APPEND SOURCES ${SOURCES_HPP} ${SOURCES_CPP})
  
  add_library( ${target_name} STATIC ${SOURCES} )
  
  if( BUILD_WCE_TESTING )
  	include_directories( src/Common/include )
  	include_directories( src/Chromogenics/include )
  	include_directories( src/Gases/include )
  	include_directories( src/Tarcog/include )  	
  	include_directories( src/SpectralAveraging/include )
  	include_directories( src/Viewer/include )
  	include_directories( src/SingleLayerOptics/include )
  	include_directories( src/MultiLayerOptics/include )
  	
  	file( GLOB all_test_src RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/Common/tst/*.cpp" )
    	LIST( APPEND test_src ${all_test_src} )
    
    	file( GLOB all_test_src RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/Gases/tst/*.cpp" )
    	LIST( REMOVE_ITEM all_test_src "src/Gases/tst/main.cpp")
    	LIST( APPEND test_src ${all_test_src} )
    
   	file( GLOB all_test_src RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/Tarcog/tst/*.cpp" )
    	LIST( REMOVE_ITEM all_test_src "src/Tarcog/tst/main.cpp")
    	LIST( APPEND test_src ${all_test_src} )
    
    	file( GLOB all_test_src RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/SpectralAveraging/tst/*.cpp" )
   	LIST( REMOVE_ITEM all_test_src "src/SpectralAveraging/tst/main.cpp")
    	LIST( APPEND test_src ${all_test_src} )
    
    	file( GLOB all_test_src RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/Viewer/tst/*.cpp" )
    	LIST( REMOVE_ITEM all_test_src "src/Viewer/tst/main.cpp")
    	LIST( APPEND test_src ${all_test_src} )
    
    	file( GLOB all_test_src RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/SingleLayerOptics/tst/*.cpp" )
    	LIST( REMOVE_ITEM all_test_src "src/SingleLayerOptics/tst/main.cpp")
    	LIST( APPEND test_src ${all_test_src} )
    
    	file( GLOB all_test_src RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/MultiLayerOptics/tst/*.cpp" )
    	LIST( REMOVE_ITEM all_test_src "src/MultiLayerOptics/tst/main.cpp")
    	LIST( APPEND test_src ${all_test_src} )
    
    	CREATE_TEST_TARGETS_WCE( ${target_name} "${test_src}" "" )
  endif()#if( BUILD_WCE_TESTING )
  
endif()#if( ${SINGLE_PROJECT} )

config_compiler_and_linker_wce()
