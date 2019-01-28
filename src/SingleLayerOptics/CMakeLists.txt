#cmake_minimum_required(VERSION 2.8.7)

message("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx")
set( target_name SingleLayerOptics )
message("xx /src/SingleLayerOptics/CMakeLists - target_name: ${target_name}")

# first include header files of this project itself
# include_directories( include )

# make sure to connect to header files of common variables
include_directories( ../Common/include )
include_directories( ../Viewer/include )
include_directories( ../SpectralAveraging/include )

# collect all source files and add them to the SOURCES list
file( GLOB SOURCES_CPP "src/*.cpp" )
file( GLOB SOURCES_HPP "src/*.hpp" )
LIST(APPEND SOURCES ${SOURCES_HPP} ${SOURCES_CPP} )

# Generates the static library from the SOURCES
add_library( ${target_name} STATIC ${SOURCES} )

target_link_libraries( ${target_name} ${LINK_TO_Common} )
target_link_libraries( ${target_name} ${LINK_TO_Viewer} )
target_link_libraries( ${target_name} ${LINK_TO_SpectralAveraging} )

# Install will be used by master projects to get information on destination of library files
install(TARGETS ${target_name}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

# create shared library with the boost.python wrapper to be imported into Python
if( NOT BUILD_WCE_TESTING )
	message("xx /src/SingleLayerOptiocs/CMakeLists.txt - boost.python library")
	add_library(BPPSLOLib SHARED bpp/BPPSLOLib.cpp ${SOURCES})
	target_link_libraries(BPPSLOLib ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} ${LINK_TO_Common} ${LINK_TO_Viewer} ${LINK_TO_SpectralAveraging})
	set_target_properties(BPPSLOLib PROPERTIES PREFIX "")
	install (TARGETS BPPSLOLib RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin
		LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/lib
		ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/lib)
endif()#if( NOT BUILD_WCE_TESTING)

if( BUILD_WCE_TESTING )
  include_directories( include )
  file( GLOB all_test_src RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" tst/*.cpp )
  set( test_src ${all_test_src} )
  CREATE_TEST_TARGETS_WCE( ${target_name} "${test_src}" "" )
endif ()

warning_level_update_wce()
