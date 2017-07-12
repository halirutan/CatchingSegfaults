cmake_minimum_required(VERSION 3.7)
project(CatchingSegfaults)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexceptions -fnon-call-exceptions")
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/Mathematica" ${CMAKE_MODULE_PATH})
set(Mathematica_ROOT_DIR "/Applications/Development/Mathematica.app/")
find_package(Mathematica 11.1)

include_directories(${Mathematica_INCLUDE_DIRS})
set(SOURCE_FILES
        library.cpp
        segvcatch.cpp
        segvcatch.h
        i386-signal.h
        x86_64-signal.h)
Mathematica_ADD_LIBRARY(CatchingSegfaults SHARED ${SOURCE_FILES})