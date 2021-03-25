cmake_minimum_required(VERSION 3.17)

set(This RaytracerTest)

set(Sources
        HelperTest.cpp
        TupleTest.cpp
        CanvasTest.cpp
        MatrixTest.cpp
        TransformTest.cpp
        IntersectionTest.cpp
        RayTest.cpp
        ShapeTest.cpp
        LightTest.cpp
        MaterialTest.cpp
        WorldTest.cpp
        CameraTest.cpp)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
        gtest_main
        Raytracer
        )

add_test(
        NAME ${This}
        COMMAND ${This}
)