cmake_minimum_required(VERSION 2.8)
set(OpenCV_STATIC	ON)
project( Assign02 )

#####################################
# Set whether we are on Linux
#####################################

if(UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif()

#####################################
# Add directory to list of places CMake looks for config files
#####################################

if(WIN32)
	set(MASTER_DEPEND "" CACHE PATH "Set this to your directory for dependencies.")	
elseif(APPLE)
	set(MASTER_DEPEND "/usr/local")
endif()

set(CMAKE_PREFIX_PATH ${MASTER_DEPEND} ${CMAKE_PREFIX_PATH})

#####################################
# Make sure we are using static runtime (under Windows and Visual Studio)
#####################################

if(WIN32 AND NOT MINGW)	
	# Solution from: https://stackoverflow.com/questions/14172856/cmake-compile-with-mt-instead-of-md
	set(CompilerFlags
	        CMAKE_CXX_FLAGS
	        CMAKE_CXX_FLAGS_DEBUG
	        CMAKE_CXX_FLAGS_RELEASE
	        CMAKE_C_FLAGS
	        CMAKE_C_FLAGS_DEBUG
	        CMAKE_C_FLAGS_RELEASE
	        )
	foreach(CompilerFlag ${CompilerFlags})
	  string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")	  
	endforeach()
endif()

#####################################
# LIST OF DEPENDENCIES:
# - OpenCV
#####################################

#####################################
# OpenCV
#####################################

find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

#####################################
# Require C++17
#####################################

if(WIN32)	
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
elseif(WIN32 AND MINGW)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif(LINUX)	
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")	
elseif(APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")	
endif()

#####################################
# Include any includes and libraries we missed
#####################################

include_directories(${MASTER_DEPEND}/include)
link_directories(${MASTER_DEPEND}/lib)

#####################################
# Get general sources
#####################################

include_directories(".")

file(GLOB GENERAL_SOURCES
    "*.h"    
    "*.cpp"  
    "*.hpp"  
)

#####################################
# Set general libraries
#####################################

set(GENERAL_LIBRARIES ${OpenCV_LIBS})

#####################################
# Extra setup
#####################################

if(APPLE)
	find_library(COCOA_LIBRARY Cocoa)
	find_library(IOKIT_LIBRARY IOKit)
	find_library(COREVIDEO_LIBRARY CoreVideo)
	set(EXTRA_LIBS ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
	set(GENERAL_LIBRARIES ${GENERAL_LIBRARIES} ${EXTRA_LIBS})
endif()

#####################################
# Create executable
#####################################

# Create executable and link libraries
add_executable(Assign02 ${GENERAL_SOURCES})
target_link_libraries(Assign02 ${GENERAL_LIBRARIES})

#####################################
# Set install target 
#####################################

install(TARGETS Assign02 RUNTIME DESTINATION bin)
