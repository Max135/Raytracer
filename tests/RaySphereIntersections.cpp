//
// Created by Max on 2021-01-10.
//

#include "../raytracer/features/Ray/Ray.h"
#include "../raytracer/features/Matrix/Matrices.h"
#include "../raytracer/features/Tuple/Tuples.h"
#include "gtest/gtest.h"
#include "../raytracer/features/Shape/Sphere.h"

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

TEST(RayTests, TestRayIntersectSphere) {
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere sphere;

    std::vector<float> intersections = ray.intersect(sphere);

    ASSERT_EQ(2, intersections.size());
    ASSERT_EQ(4.0, intersections[0]);
    ASSERT_EQ(6.0, intersections[1]);
}

TEST(RayTests, TestRayIntersectSphereTangent) {
    Ray ray(Point(0, 1, -5), Vector(0, 0, 1));
    Sphere sphere;

    std::vector<float> intersections = ray.intersect(sphere);

    ASSERT_EQ(2, intersections.size());
    ASSERT_EQ(5.0, intersections[0]);
    ASSERT_EQ(5.0, intersections[1]);
}

TEST(RayTests, TestRayIntersectionMiss) {
    Ray ray(Point(0, 2, -5), Vector(0, 0, 1));
    Sphere sphere;

    std::vector<float> intersections = ray.intersect(sphere);

    ASSERT_EQ(0, intersections.size());
}

TEST(RayTests, TestRayInsideSphere) {
    Ray ray(Point(0, 0, 0), Vector(0, 0, 1));
    Sphere sphere;

    std::vector<float> intersections = ray.intersect(sphere);

    ASSERT_EQ(2, intersections.size());
    ASSERT_EQ(-1.0, intersections[0]);
    ASSERT_EQ(1.0, intersections[1]);
}

TEST(RayTests, TestRayFrontSphere) {
    Ray ray(Point(0, 0, 5), Vector(0, 0, 1));
    Sphere sphere;

    std::vector<float> intersections = ray.intersect(sphere);

    ASSERT_EQ(2, intersections.size());
    ASSERT_EQ(-6.0, intersections[0]);
    ASSERT_EQ(-4.0, intersections[1]);
}
