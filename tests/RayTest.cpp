//
// Created by Max on 2021-01-24.
//

#include "gtest/gtest.h"
#include "../raytracer/features/Ray/Ray.h"

// Creating and querying a ray
TEST(RayTests, TestRayCreation) {
    Point origin(1, 2, 3);
    Vector direction(4, 5, 6);
    Ray ray(origin, direction);

    ASSERT_TRUE(origin == ray.origin);
    ASSERT_TRUE(direction == ray.direction);
}

// Computing a point from a distance
TEST(RayTests, TestPosition) {
    Ray ray(Point(2, 3, 4), Vector(1, 0, 0));

    ASSERT_TRUE(Point(2, 3, 4) == ray.position(0));
    ASSERT_TRUE(Point(3, 3, 4) == ray.position(1));
    ASSERT_TRUE(Point(1, 3, 4) == ray.position(-1));
    ASSERT_TRUE(Point(4.5, 3, 4) == ray.position(2.5));
}

// A ray intersects a sphere at two points
TEST(RayTests, TestRayIntersectSphere) {
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere sphere;

    Intersections intersections = ray.intersect(&sphere);

    ASSERT_EQ(2, intersections.size());
    ASSERT_EQ(4.0, intersections[0].t);
    ASSERT_EQ(6.0, intersections[1].t);
}

// A ray intersects a sphere at a tangent
TEST(RayTests, TestRayIntersectSphereTangent) {
    Ray ray(Point(0, 1, -5), Vector(0, 0, 1));
    Sphere sphere;

    Intersections intersections = ray.intersect(&sphere);

    ASSERT_EQ(2, intersections.size());
    ASSERT_EQ(5.0, intersections[0].t);
    ASSERT_EQ(5.0, intersections[1].t);
}

// A ray misses a sphere
TEST(RayTests, TestRayIntersectionMiss) {
    Ray ray(Point(0, 2, -5), Vector(0, 0, 1));
    Sphere sphere;

    Intersections intersections = ray.intersect(&sphere);

    ASSERT_EQ(0, intersections.size());
}

// A ray originates inside a sphere
TEST(RayTests, TestRayInsideSphere) {
    Ray ray(Point(0, 0, 0), Vector(0, 0, 1));
    Sphere sphere;

    Intersections intersections = ray.intersect(&sphere);

    ASSERT_EQ(2, intersections.size());
    ASSERT_EQ(-1.0, intersections[0].t);
    ASSERT_EQ(1.0, intersections[1].t);
}

// A sphere is behind a ray
TEST(RayTests, TestRayFrontSphere) {
    Ray ray(Point(0, 0, 5), Vector(0, 0, 1));
    Sphere sphere;

    Intersections intersections = ray.intersect(&sphere);

    ASSERT_EQ(2, intersections.size());
    ASSERT_EQ(-6.0, intersections[0].t);
    ASSERT_EQ(-4.0, intersections[1].t);
}

// Translating a ray
TEST(RayTests, TestTranslation) {
    Ray ray(Point(1, 2, 3), Vector(0, 1, 0));
    Transform t = Transform::translation(3, 4, 5);

    Ray ray2 = ray.transform(&t);

    ASSERT_TRUE(ray2.origin == Point(4, 6, 8));
    ASSERT_TRUE(ray2.direction == Vector(0, 1, 0));
}

// Scaling a ray
TEST(RayTests, TestScalling) {
    Ray ray(Point(1, 2, 3), Vector(0, 1, 0));
    Transform s = Transform::scaling(2, 3, 4);

    Ray ray2 = ray.transform(&s);

    ASSERT_TRUE(ray2.origin == Point(2, 6, 12));
    ASSERT_TRUE(ray2.direction == Vector(0, 3, 0));
}

// Intersecting a scaled sphere with a ray
TEST(RayTests, TestIntersectionScalledSphere) {
    Ray r(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s;
    s.setTransform(Transform::scaling(2, 2, 2));

    Intersections xs = r.intersect(&s);

    ASSERT_EQ(2, xs.size());
    ASSERT_EQ(3, xs[0].t);
    ASSERT_EQ(7, xs[1].t);
}

// Intersecting a translated sphere with a ray
TEST(RayTests, TestIntersectionTranslatedSphere) {
    Ray r(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s;
    s.setTransform(Transform::translation(5, 0, 0));

    Intersections xs = r.intersect(&s);

    ASSERT_EQ(0, xs.size());
}

// Precomputing the state of an intersection
TEST(RayTests, TestPrecomputation) {
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere shape;
    Intersection i(4, &shape);
    preComps comps = ray.prepareComputations(i);

    ASSERT_EQ(i.t, comps.t);
    ASSERT_TRUE(shape == *comps.object);
    ASSERT_TRUE(Point(0, 0, -1) == comps.point);
    ASSERT_TRUE(Vector(0, 0, -1) == comps.eyeV);
    ASSERT_TRUE(Vector(0, 0, -1) == comps.normalV);
}

// The hit, when an intersection occurs on the outside
TEST(RayTests, TestIntersectionOutside) {
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere shape;
    Intersection i(4, &shape);
    preComps comps = ray.prepareComputations(i);

    ASSERT_EQ(false, comps.inside);
}

// The hit, when an intersection occurs on the inside
TEST(RayTests, TestIntersectionInside) {
    Ray ray(Point(0, 0, 0), Vector(0, 0, 1));
    Sphere shape;
    Intersection i(1, &shape);
    preComps comps = ray.prepareComputations(i);

    ASSERT_TRUE(Point(0, 0, 1) == comps.point);
    ASSERT_TRUE(Vector(0, 0, -1) == comps.eyeV);
    ASSERT_EQ(true, comps.inside);
    //Normal would have been (0, 0, 1), but is inverted
    ASSERT_TRUE(Vector(0, 0, -1) == comps.normalV);
}
