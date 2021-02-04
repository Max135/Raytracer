//
// Created by Max on 2021-01-27.
//

#include "gtest/gtest.h"
#include "../raytracer/features/Shape/Shapes.h"

TEST(SphereTests, TestDefaultTransform) {
    Sphere s;

    ASSERT_TRUE(Matrix::identityMatrix() == s.transform);
}

TEST(SphereTests, TestSettingTransform) {
    Sphere s;
    Transform t = Transform::translation(2, 3, 4);
    s.setTransform(t);

    ASSERT_TRUE(t == s.transform);
}

TEST(SphereTests, TestNormalXAxis) {
    Sphere s;
    Tuple n = s.normalAt(Point(1, 0, 0));

    ASSERT_TRUE(Vector(1, 0, 0) == n);
}

TEST(SphereTests, TestNormalYAxis) {
    Sphere s;
    Tuple n = s.normalAt(Point(0, 1, 0));

    ASSERT_TRUE(Vector(0, 1, 0) == n);
}

TEST(SphereTests, TestNormalZAxis) {
    Sphere s;
    Tuple n = s.normalAt(Point(0, 0, 1));

    ASSERT_TRUE(Vector(0, 0, 1) == n);
}

TEST(SphereTests, TestNormalNonAxialPoint) {
    Sphere s;
    Tuple n = s.normalAt(Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

    ASSERT_TRUE(Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3) == n);
}

TEST(SphereTests, TestNormalIsNormalized) {
    Sphere s;
    Tuple n = s.normalAt(Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

    ASSERT_TRUE(n.normalize() == n);
}

TEST(SphereTests, TestNormalTranslated) {
    Sphere s;
    s.setTransform(Transform::translation(0, 1, 0));
    Tuple n = s.normalAt(Point(0, 1.70711, -0.70711));

    ASSERT_TRUE(Vector(0, 0.70711, -0.70711) == n);
}

TEST(SphereTests, TestNormalTransformed) {
    Sphere s;
    Transform m = Transform::scaling(1, 0.5, 1).rotateZ(M_PI / 5);
    s.setTransform(m);

    Tuple n = s.normalAt(Point(0, sqrt(2) / 2.0, -sqrt(2) / 2.0));
    ASSERT_TRUE(Vector(0, 0.97014, -0.24254) == n);
}