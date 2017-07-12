cmake_minimum_required(VERSION 3.7)
project(CatchingSegfaults)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/Mathematica" ${CMAKE_MODULE_PATH})
set(Mathematica_ROOT_DIR "/usr/local/Wolfram/Mathematica/11.1")
find_package(Mathematica 11.1)

include_directories(${Mathematica_INCLUDE_DIRS})
set(SOURCE_FILES library.c)
Mathematica_ADD_LIBRARY(CatchingSegfaults SHARED ${SOURCE_FILES})