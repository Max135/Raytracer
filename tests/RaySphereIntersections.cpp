//
// Created by Max on 2021-01-10.
//

#include "../raytracer/features/Ray/Ray.h"
#include "gtest/gtest.h"

TEST(RayTests, TestRayIntersectSphere) {
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere sphere;

    std::vector<Intersection> intersections = ray.intersect(sphere);

    ASSERT_EQ(2, intersections.size());
    ASSERT_EQ(4.0, intersections[0].t);
    ASSERT_EQ(6.0, intersections[1].t);
}

TEST(RayTests, TestRayIntersectSphereTangent) {
    Ray ray(Point(0, 1, -5), Vector(0, 0, 1));
    Sphere sphere;

    std::vector<Intersection> intersections = ray.intersect(sphere);

    ASSERT_EQ(2, intersections.size());
    ASSERT_EQ(5.0, intersections[0].t);
    ASSERT_EQ(5.0, intersections[1].t);
}

TEST(RayTests, TestRayIntersectionMiss) {
    Ray ray(Point(0, 2, -5), Vector(0, 0, 1));
    Sphere sphere;

    std::vector<Intersection> intersections = ray.intersect(sphere);

    ASSERT_EQ(0, intersections.size());
}

TEST(RayTests, TestRayInsideSphere) {
    Ray ray(Point(0, 0, 0), Vector(0, 0, 1));
    Sphere sphere;

    std::vector<Intersection> intersections = ray.intersect(sphere);

    ASSERT_EQ(2, intersections.size());
    ASSERT_EQ(-1.0, intersections[0].t);
    ASSERT_EQ(1.0, intersections[1].t);
}

TEST(RayTests, TestRayFrontSphere) {
    Ray ray(Point(0, 0, 5), Vector(0, 0, 1));
    Sphere sphere;

    std::vector<Intersection> intersections = ray.intersect(sphere);

    ASSERT_EQ(2, intersections.size());
    ASSERT_EQ(-6.0, intersections[0].t);
    ASSERT_EQ(-4.0, intersections[1].t);
}
