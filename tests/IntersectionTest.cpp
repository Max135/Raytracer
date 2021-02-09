//
// Created by Max on 2021-01-20.
//

#include "gtest/gtest.h"
#include "../raytracer/features/Shape/Sphere.h"
#include "../raytracer/features/Intersection/Intersections.h"
#include "../raytracer/features/Ray/Ray.h"

// An intersection encapsulates t and object
TEST(IntersectionTests, TestCreation) {
    Sphere sphere;
    float point = 3.5;

    Intersection intersection(point, &sphere);

    ASSERT_EQ(point, intersection.t);
    ASSERT_EQ(&sphere, intersection.sphere);
}

// Aggregating intersections
TEST(IntersectionTests, TestAggregation) {
    Sphere s;

    Intersection i1(1, &s);
    Intersection i2(2, &s);
    Intersection i3(3, &s);

    Intersections xs = Intersections::intersections<Intersection>(i1, i2, i3);

    Intersection i4(4, &s);

    Intersections ss = Intersections::intersections(i4, i2, i1, i3);

    ASSERT_EQ(3, xs.size());
    ASSERT_EQ(1, xs[0].t);
    ASSERT_EQ(2, xs[1].t);
    ASSERT_EQ(3, xs[2].t);

    ASSERT_EQ(4, ss.size());
    ASSERT_EQ(1, ss[0].t);
    ASSERT_EQ(2, ss[1].t);
    ASSERT_EQ(3, ss[2].t);
    ASSERT_EQ(4, ss[3].t);
}

// The hit, when all intersections have positive t
TEST(IntersectionTests, TestHitsPositive) {
    Sphere s;

    Intersection i1(1, &s);
    Intersection i2(2, &s);
    Intersections xs = Intersections::intersections(i2, i1);

    Intersection i = xs.hit();

    ASSERT_TRUE(i == i1);
}

// The hit, when some intersections have negative t
TEST(IntersectionTests, TestHitsMix) {
    Sphere s;

    Intersection i1(-1, &s);
    Intersection i2(1, &s);
    Intersections xs = Intersections::intersections(i2, i1);

    Intersection i = xs.hit();

    ASSERT_TRUE(i == i2);
}

// The hit, when all intersections have negative t
TEST(IntersectionTests, TestHitsNegative) {
    Sphere s;

    Intersection i1(-2, &s);
    Intersection i2(-1, &s);
    Intersections xs = Intersections::intersections(i2, i1);

    Intersection i = xs.hit();

    ASSERT_TRUE(i == Intersection());
}

// The hit is always the lowest non negative intersection
TEST(IntersectionTests, TestGoodHit) {
    Sphere s;

    Intersection i1(5, &s);
    Intersection i2(7, &s);
    Intersection i3(-3, &s);
    Intersection i4(2, &s);

    Intersections xs = Intersections::intersections(i1, i2, i3, i4);

    Intersection i = xs.hit();

    ASSERT_TRUE(i == i4);
}
