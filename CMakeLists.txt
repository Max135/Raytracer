cmake_minimum_required(VERSION 3.17)

set(This Raytracer)
set(CMAKE_CXX_STANDARD 14)

project(${This} CXX)

enable_testing()

add_subdirectory(googletest)

set(Headers
        raytracer/features/Helper.h
        raytracer/features/Tuple/Tuple.h
        raytracer/features/Tuple/Vector.h
        raytracer/features/Tuple/Color.h
        raytracer/features/Tuple/Point.h
        raytracer/features/Canvas/Canvas.h
        raytracer/features/Matrix/Matrix.h
        raytracer/features/Matrix/Transform.h
        raytracer/features/Tuple/Tuples.h
        raytracer/features/Matrix/Matrices.h
        raytracer/features/Ray/Ray.h
        raytracer/features/Shape/Sphere.h
        raytracer/features/Intersection/Intersection.h
        raytracer/features/Shape/Shapes.h
        raytracer/features/Light/Light.h
        raytracer/features/Material/Material.h)

set(Sources
        raytracer/features/Helper.cpp
        raytracer/features/Tuple/Tuple.cpp
        raytracer/features/Tuple/Vector.cpp
        raytracer/features/Tuple/Point.cpp
        raytracer/features/Tuple/Color.cpp
        raytracer/features/Canvas/Canvas.cpp
        raytracer/features/Matrix/Matrix.cpp
        raytracer/features/Matrix/Transform.cpp
        raytracer/features/Ray/Ray.cpp
        raytracer/features/Shape/Sphere.cpp
        raytracer/features/Intersection/Intersection.cpp
        raytracer/features/Light/Light.cpp
        raytracer/features/Material/Material.cpp
        main.cpp)

add_library(${This} STATIC ${Sources} ${Headers})

add_executable(RaytracerRun ${Sources} ${Headers})

add_subdirectory(tests)