cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)
project(smtk_multiblock_reader)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(NOT ParaView_SOURCE_DIR)
  cmake_minimum_required(VERSION 2.8)

  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

  find_package(ParaView REQUIRED)
  include(${PARAVIEW_USE_FILE})
else()
  include_directories(${VTK_INCLUDE_DIRS})
endif()

include(ParaViewPlugins)

find_package(SMTK REQUIRED COMPONENTS smtkCore smtkCGMSession vtkSMTKReaderExt)

add_subdirectory(src)
