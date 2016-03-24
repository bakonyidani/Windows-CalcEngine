# Make sure expat is compiled as a static library
# ADD_DEFINITIONS("-DXML_STATIC")

IF ( CMAKE_COMPILER_IS_GNUCXX OR "x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xClang" ) # g++/Clang
	set(LINKER_FLAGS "")
	mark_as_advanced(ENABLE_THREAD_SANITIZER ENABLE_ADDRESS_SANITIZER ENABLE_UNDEFINED_SANITIZER)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${LINKER_FLAGS}")

    # COMPILER FLAGS
    ADD_CXX_DEFINITIONS("-pipe") # Faster compiler processing
    # set (CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
    ADD_CXX_DEFINITIONS("-std=c++11") # Enable C++11 features in g++
    ADD_CXX_DEFINITIONS("-pedantic") # Turn on warnings about constructs/situations that may be non-portable or outside of the standard
    ADD_CXX_DEFINITIONS("-ffor-scope")
    ADD_CXX_DEFINITIONS("-Wall -Wextra") # Turn on warnings
    ADD_CXX_DEFINITIONS("-Wno-unknown-pragmas")
    if( CMAKE_COMPILER_IS_GNUCXX ) # g++
      ADD_CXX_DEFINITIONS("-Wno-unused-but-set-parameter -Wno-unused-but-set-variable") # Suppress unused-but-set warnings until more serious ones are addressed
      ADD_CXX_DEFINITIONS("-Wno-maybe-uninitialized")
    elseif( "x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xClang" )
      ADD_CXX_DEFINITIONS("-Wno-invalid-source-encoding")
    endif()

    # ADDITIONAL DEBUG-MODE-SPECIFIC FLAGS
    if ( CMAKE_COMPILER_IS_GNUCXX ) # g++
      ADD_CXX_DEBUG_DEFINITIONS("-ffloat-store") # Improve debug run solution stability
      ADD_CXX_DEBUG_DEFINITIONS("-fsignaling-nans") # Disable optimizations that may have concealed NaN behavior
    endif ()
  
  ADD_CXX_DEBUG_DEFINITIONS("-ggdb") # Produces debugging information specifically for gdb
ENDIF ()