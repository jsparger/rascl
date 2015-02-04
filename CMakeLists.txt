#----------------------------------------------------------------------------
# Set up the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(rascl)
set(target rascl)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_CXX_FLAGS "-pthread -std=c++14 -framework OpenCL")

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
# NOTE: [^.]*.cc means match all files ending in .cc
# 	except those that start with a "." (period) (hidden)
#file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE sources  
	${SRC_DIR}/[^.]*.cc 
	${SRC_DIR}/[^.]*.cpp 
	${SRC_DIR}/[^.]*.cxx 
	${SRC_DIR}/[^.]*.c
)

set(DICT_DIR ${PROJECT_SOURCE_DIR}/dict)
file(GLOB_RECURSE dictionaries
	${DICT_DIR}/[^.]*.cpp
)

#file(GLOB_RECURSE headers ${PROJECT_SOURCE_DIR}/include/*)
set(INC_DIR ${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE headers ${PROJECT_SOURCE_DIR}/include/ 
	${INC_DIR}/[^.]*.hh 
	${INC_DIR}/[^.]*.h 
	${INC_DIR}/[^.]*.hpp 
	${INC_DIR}/[^.]*.hxx 
)
include_directories("${PROJECT_SOURCE_DIR}/include")
message(STATUS "${sources}")


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(${target} main.cc ${sources} ${dictionaries} ${headers})

# opencl
#----------------------------------------------------------------------------
# target_link_libraries (${target} OpenCL)

# boost compute
#----------------------------------------------------------------------------
include_directories("$ENV{HOME}/local/compute/include")
include_directories("$ENV{HOME}/local/boost/boost_1_55_0/boost_install/include")

# for <= geant4.9.4 (probably still works with 4.9.5 but better to use provided
# find file.
#----------------------------------------------------------------------------
# Add geant4 libs and include files
# G4_INCLUDE_DIRS can be gotten by the following command: 
# export G4_INCLUDE_DIRS=`find source -name include -type d`
# include_directories($ENV{G4_INCLUDE_DIRS})
#
# # geant4 libs
# file(GLOB g4libs $ENV{G4LIB}/$ENV{G4SYSTEM}/*.so)
# message(STATUS ${g4libs})
# target_link_libraries(${target} ${g4libs})

# for geant4.9.5
#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
#option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
#if(WITH_GEANT4_UIVIS)
#  find_package(Geant4 REQUIRED ui_all vis_all)
#else()
#  find_package(Geant4 REQUIRED)
#endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
#include(${Geant4_USE_FILE})
#include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Setup Cern ROOT
#
# Find ROOT, failing if we don't locate it (the REQUIRED flag)
#find_package(ROOT REQUIRED)
#if ( NOT ROOT_FOUND )
#  message(FATAL_ERROR "Package ROOT required, but not found!")
#endif( NOT ROOT_FOUND )
# message(STATUS "Include=${ROOT_INCLUDE_DIRS}  Libs=${ROOT_LIBRARIES}")


# so the above would be great, except the Geant4 FindROOT.cmake file tries to
# find the libs in ROOTSYS/lib/root/ and the includes in ROOTSYS/include/root 
# for some reason...
# so we'll just type it manually. I just copied what was output by the message
# command after find_package(ROOT REQUIRED) and fixed the directories.
# NOTE! -lReflexDict and -lReflex are needed to link the Reflex libraries
#execute_process(COMMAND root-config --libs OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE ROOT_LIBRARIES)
#message(STATUS "ROOTLIBRARIES = ${ROOT_LIBRARIES}")
#set(ROOT_LIBRARIES "-L$ENV{ROOTSYS}/lib -lGui -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -lrdynamic -lReflexDict -lReflex")
# set(ROOT_LIBRARIES "-L$ENV{ROOTSYS}/lib -lGui -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -lReflexDict -lReflex")
# #set(ROOT_LIBRARIES "-L/Users/johnsparger/local/root/lib/root -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lpthread -lm -ldl")
# set(ROOT_INCLUDE_DIRS "$ENV{ROOTSYS}/include")
# include_directories(${ROOT_INCLUDE_DIRS})
# set(LIBS ${LIBS} ${ROOT_LIBRARIES})
# target_link_libraries(${target} ${LIBS})
#message(STATUS "Include=${ROOT_INCLUDE_DIRS}  Libs=${ROOT_LIBRARIES}")

# new attempt:
#include(FindROOT.cmake)
#include_directories( ${ROOT_INCLUDE_DIR} )
#link_directories( ${ROOT_LIBRARY_DIR})
#----------------------------------------------------------------------------
# Setup Boost Libraries
# include_directories("$ENV{HOME}/local/boost/boost_1_53_0/")
#TARGET_LINK_LIBRARIES(${target} $ENV{HOME}/local/boost/boost_1_53_0/lib/libboost_thread.so)
#TARGET_LINK_LIBRARIES(${target} $ENV{HOME}/local/boost/boost_1_53_0/lib/libboost_system.so)

# Set up CLHEP # 
#----------------------------------------------------------------------------
#include the CLHEP include directory
# include_directories($ENV{CLHEP_INCLUDE_DIR})
#
# # clhep libs
# # apparently only this one lib needs to be loaded.
# file(GLOB clheplibs $ENV{CLHEP_LIB_DIR}/libCLHEP.so)
# message(STATUS ${clheplibs})
# TARGET_LINK_LIBRARIES(${target} ${clheplibs})
#

# Set up ZeroMQ  
#----------------------------------------------------------------------------
# include the header directory for zmq
# include_directories($ENV{ZEROMQ_INCLUDE_DIR})
# # include the header directory for cppzmq, the c++ binding for zeromq
# include_directories($ENV{CPPZMQ_INCLUDE_DIR})
#
# # add the libs
# file(GLOB zmqlibs $ENV{ZEROMQ_LIB_DIR}/libzmq.so)
# target_link_libraries(${target}  ${zmqlibs})
#


#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
#install(TARGETS ${target} DESTINATION bin)


