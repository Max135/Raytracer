cmake_minimum_required(VERSION 3.17)

set(This Raytracer)
set(CMAKE_CXX_STANDARD 14)

project(${This} CXX)

enable_testing()

add_subdirectory(googletest)

set(Headers
        raytracer/features/Helper.h
        raytracer/features/Tuple.h)

set(Sources
        raytracer/features/Helper.cpp
        raytracer/features/Tuple.cpp
        main.cpp)

add_library(${This} STATIC ${Sources} ${Headers})

add_executable(RaytracerRun ${Sources} ${Headers})

add_subdirectory(tests)