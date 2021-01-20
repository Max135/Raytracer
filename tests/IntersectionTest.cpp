//
// Created by Max on 2021-01-20.
//

#include "gtest/gtest.h"
#include "../raytracer/features/Shape/Sphere.h"
#include "../raytracer/features/Intersection/Intersection.h"

TEST(IntersectionTests, TestCreation) {
    Sphere sphere;
    float point = 3.5;

    Intersection intersection(point, &sphere);

    ASSERT_EQ(point, intersection.t);
    ASSERT_EQ(&sphere, intersection.sphere);
}

TEST(IntersectionTests, TestAggregation) {
    Sphere s;

    Intersection i1(1, &s);
    Intersection i2(2, &s);

    std::vector<Intersection> xs = Intersection::intersections(i1, i2);

    ASSERT_EQ(2, xs.size());
    ASSERT_EQ(1, xs[0].t);
    ASSERT_EQ(2, xs[1].t);
}
