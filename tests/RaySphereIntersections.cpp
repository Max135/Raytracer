//
// Created by Max on 2021-01-10.
//

#include "../raytracer/features/Ray/Ray.h"
#include "../raytracer/features/Matrix/Matrices.h"
#include "../raytracer/features/Tuple/Tuples.h"
#include "gtest/gtest.h"

TEST(RayTests, TestRayCreation) {
    Point origin(1, 2, 3);
    Vector direction(4, 5, 6);
    Ray ray(origin, direction);

    ASSERT_TRUE(origin == ray.origin);
    ASSERT_TRUE(direction == ray.direction);
}

TEST(RayTests, TestPosition) {
    Ray ray(Point(2, 3, 4), Vector(1, 0, 0));

    ASSERT_TRUE(Point(2, 3, 4) == ray.position(0));
    ASSERT_TRUE(Point(3, 3, 4) == ray.position(1));
    ASSERT_TRUE(Point(1, 3, 4) == ray.position(-1));
    ASSERT_TRUE(Point(4.5, 3, 4) == ray.position(2.5));
}
