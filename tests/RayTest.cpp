//
// Created by Max on 2021-01-24.
//

#include "gtest/gtest.h"
#include "../raytracer/features/Ray/Ray.h"
#include "../raytracer/features/Matrix/Matrices.h"

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

TEST(RayTests, TestTranslation) {
    Ray ray(Point(1, 2, 3), Vector(0, 1, 0));
    Transform t = Transform::translation(3, 4, 5);

    Ray ray2 = ray.transform(&t);

    ASSERT_TRUE(ray2.origin == Point(4, 6, 8));
    ASSERT_TRUE(ray2.direction == Vector(0, 1, 0));
}

TEST(RayTests, TestScalling) {
    Ray ray(Point(1, 2, 3), Vector(0, 1, 0));
    Transform s = Transform::scaling(2, 3 ,4);

    Ray ray2 = ray.transform(&s);

    ASSERT_TRUE(ray2.origin == Point(2, 6, 12));
    ASSERT_TRUE(ray2.direction == Vector(0, 3, 0));
}
