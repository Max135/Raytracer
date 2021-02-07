//
// Created by Max on 2021-02-03.
//

#include "../raytracer/features/Light/Light.h"
#include "gtest/gtest.h"

// A point light has a position and intensity
TEST(LightTests, TestPositionAndIntensity) {
    Color intensity(1, 1, 1);
    Point position(0, 0, 0);
    Light light(Point(0, 0, 0), intensity);

    ASSERT_TRUE(position == light.position);
    ASSERT_TRUE(intensity == light.intensity);
}
