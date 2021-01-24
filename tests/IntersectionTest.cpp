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
    Intersection i3(3, &s);

    std::vector<Intersection> xs = Intersection::intersections<Intersection>(i1, i2, i3);

    Intersection i4(4, &s);

    std::vector<Intersection> ss = Intersection::intersections(i1, i2, i3, i4);

    ASSERT_EQ(3, xs.size());
    ASSERT_EQ(1, xs[0].t);
    ASSERT_EQ(2, xs[1].t);
    ASSERT_EQ(3, xs[2].t);

    ASSERT_EQ(4, ss.size());
}
