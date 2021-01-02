cmake_minimum_required(VERSION 3.17)

set(This Raytracer)
set(CMAKE_CXX_STANDARD 14)

project(${This} CXX)

enable_testing()

add_subdirectory(googletest)

set(Headers
        raytracer/Helper.h
        raytracer/Tuple.h)

set(Sources
        raytracer/Helper.cpp
        raytracer/Tuple.cpp)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(tests)