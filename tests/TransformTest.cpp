//
// Created by Max on 2021-01-05.
//

#include <cmath>
#include "../raytracer/features/Matrix/Matrices.h"
#include "gtest/gtest.h"

TEST(TransformTests, TestTranslationMatrixMultiplication) {
    Transform transform = Transform::translation(5, -3, 2);
    Point point(-3, 4, 5);

    ASSERT_TRUE(Point(2, 1, 7) == transform * point);
}

TEST(TransformTests, TestTranlationInverseMultiplication) {
    Transform transform = Transform::translation(5, -3, 2);
    Point point(-3, 4, 5);

    ASSERT_TRUE(Point(-8, 7, 3) == transform.inverse() * point);
}

TEST(TransformTests, TestVectorMultiplication) {
    Transform transform = Transform::translation(5, -3, 2);
    Vector vector(-3, 4, 5);

    ASSERT_TRUE(vector == transform * vector);
}

TEST(TransformTests, TestScallingPoint) {
    Transform transform = Transform::scaling(2, 3, 4);
    Point point(-4 ,6, 8);

    ASSERT_TRUE(Point(-8, 18, 32) == transform * point);
}

TEST(TransformTests, TestScallingVector) {
    Transform transform = Transform::scaling(2, 3, 4);
    Vector vector(-4 ,6, 8);

    ASSERT_TRUE(Vector(-8, 18, 32) == transform * vector);
}

TEST(TransformTests, TestScallingInverse) {
    Transform transform = Transform::scaling(2, 3, 4);
    Vector vector(-4 ,6, 8);

    ASSERT_TRUE(Vector(-2, 2, 2) == transform.inverse() * vector);
}

TEST(TransformTests, TestReflection) {
    Transform transform = Transform::scaling(-1, 1, 1);
    Point point(2, 3, 4);

    ASSERT_TRUE(Point(-2, 3, 4) == transform * point);
}

TEST(TransformTests, TestRotationX) {
    Point point(0, 1, 0);
    Transform halfQuarter = Transform::xRotation(M_PI_4);
    Transform fullQuarter = Transform::xRotation(M_PI_2);

    ASSERT_TRUE(Point(0, sqrt(2) / 2, sqrt(2) / 2) == halfQuarter * point);
    ASSERT_TRUE(Point(0, 0, 1) == fullQuarter * point);
}

TEST(TransformTests, TestInverseRotationX) {
    Point point(0, 1, 0);
    Transform halfQuarter = Transform::xRotation(M_PI_4);

    ASSERT_TRUE(Point(0, sqrt(2) / 2, -sqrt(2) / 2) == halfQuarter.inverse() * point);
}

TEST(TransformTests, TestRotationY) {
    Point point(0, 0, 1);
    Transform halfQuarter = Transform::yRotation(M_PI_4);
    Transform fullQuarter = Transform::yRotation(M_PI_2);

    ASSERT_TRUE(Point(sqrt(2) / 2, 0, sqrt(2) / 2) == halfQuarter * point);
    ASSERT_TRUE(Point(1, 0, 0) == fullQuarter * point);
}

TEST(TransformTests, TestRotationZ) {
    Point point(0, 1, 0);
    Transform halfQuarter = Transform::zRotation(M_PI_4);
    Transform fullQuarter = Transform::zRotation(M_PI_2);

    ASSERT_TRUE(Point(-sqrt(2) / 2, sqrt(2) / 2, 0) == halfQuarter * point);
    ASSERT_TRUE(Point(-1, 0, 0) == fullQuarter * point);
}

TEST(TransformTests, TestShearing) {
    Transform transformXY = Transform::shearing(1, 0, 0, 0, 0, 0);
    Point point(2, 3, 4);
    ASSERT_TRUE(Point(5, 3, 4) == transformXY * point);

    Transform transformXZ = Transform::shearing(0, 1, 0, 0, 0, 0);
    ASSERT_TRUE(Point(6, 3, 4) == transformXZ * point);

    Transform transformYX = Transform::shearing(0, 0, 1, 0, 0, 0);
    ASSERT_TRUE(Point(2, 5, 4) == transformYX * point);

    Transform transformYZ = Transform::shearing(0, 0, 0, 1, 0, 0);
    ASSERT_TRUE(Point(2, 7, 4) == transformYZ * point);

    Transform transformZX = Transform::shearing(0, 0, 0, 0, 1, 0);
    ASSERT_TRUE(Point(2, 3, 6) == transformZX * point);

    Transform transformZY = Transform::shearing(0, 0, 0, 0, 0, 1);
    ASSERT_TRUE(Point(2, 3, 7) == transformZY * point);
}