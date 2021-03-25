//
// Created by Max on 2021-01-05.
//

#include <cmath>
#include "../raytracer/features/Matrix/Matrices.h"
#include "gtest/gtest.h"

Transform initResultMatrix();

// Multiplying by a translation matrix
TEST(TransformTests, TestTranslationMatrixMultiplication) {
    Transform transform = Transform::translation(5, -3, 2);
    Point point(-3, 4, 5);

    ASSERT_TRUE(Point(2, 1, 7) == transform * point);
}

// Multiplying by the inverse of a translation matrix
TEST(TransformTests, TestTranlationInverseMultiplication) {
    Transform transform = Transform::translation(5, -3, 2);
    Point point(-3, 4, 5);

    ASSERT_TRUE(Point(-8, 7, 3) == transform.inverse() * point);
}

// Translation does not affect vectors
TEST(TransformTests, TestVectorMultiplication) {
    Transform transform = Transform::translation(5, -3, 2);
    Vector vector(-3, 4, 5);

    ASSERT_TRUE(vector == transform * vector);
}

// A scaling matrix applied to a point
TEST(TransformTests, TestScallingPoint) {
    Transform transform = Transform::scaling(2, 3, 4);
    Point point(-4, 6, 8);

    ASSERT_TRUE(Point(-8, 18, 32) == transform * point);
}

// A scaling matrix applied to a vector
TEST(TransformTests, TestScallingVector) {
    Transform transform = Transform::scaling(2, 3, 4);
    Vector vector(-4, 6, 8);

    ASSERT_TRUE(Vector(-8, 18, 32) == transform * vector);
}

// Multiplying by the inverse of a scaling matrix
TEST(TransformTests, TestScallingInverse) {
    Transform transform = Transform::scaling(2, 3, 4);
    Vector vector(-4, 6, 8);

    ASSERT_TRUE(Vector(-2, 2, 2) == transform.inverse() * vector);
}

// Reflection is scaling by a negative value
TEST(TransformTests, TestReflection) {
    Transform transform = Transform::scaling(-1, 1, 1);
    Point point(2, 3, 4);

    ASSERT_TRUE(Point(-2, 3, 4) == transform * point);
}

// Rotating a point around the x axis
TEST(TransformTests, TestRotationX) {
    Point point(0, 1, 0);
    Transform halfQuarter = Transform::xRotation(M_PI_4);
    Transform fullQuarter = Transform::xRotation(M_PI_2);

    ASSERT_TRUE(Point(0, sqrt(2) / 2, sqrt(2) / 2) == halfQuarter * point);
    ASSERT_TRUE(Point(0, 0, 1) == fullQuarter * point);
}

// The inverse of an x-rotation rotates in the opposite direction
TEST(TransformTests, TestInverseRotationX) {
    Point point(0, 1, 0);
    Transform halfQuarter = Transform::xRotation(M_PI_4);

    ASSERT_TRUE(Point(0, sqrt(2) / 2, -sqrt(2) / 2) == halfQuarter.inverse() * point);
}

// Rotating a point around the y axis
TEST(TransformTests, TestRotationY) {
    Point point(0, 0, 1);
    Transform halfQuarter = Transform::yRotation(M_PI_4);
    Transform fullQuarter = Transform::yRotation(M_PI_2);

    ASSERT_TRUE(Point(sqrt(2) / 2, 0, sqrt(2) / 2) == halfQuarter * point);
    ASSERT_TRUE(Point(1, 0, 0) == fullQuarter * point);
}

// Rotating a point around the z axis
TEST(TransformTests, TestRotationZ) {
    Point point(0, 1, 0);
    Transform halfQuarter = Transform::zRotation(M_PI_4);
    Transform fullQuarter = Transform::zRotation(M_PI_2);

    ASSERT_TRUE(Point(-sqrt(2) / 2, sqrt(2) / 2, 0) == halfQuarter * point);
    ASSERT_TRUE(Point(-1, 0, 0) == fullQuarter * point);
}

// Shearing transformation moves an axis in proportion to an other
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

// Individual transformations are applied in sequence
TEST(TransformTests, TestSequence) {
    Transform rotation = Transform::xRotation(M_PI_2);
    Transform scale = Transform::scaling(5, 5, 5);
    Transform translate = Transform::translation(10, 5, 7);

    Point point1(1, 0, 1);

    Tuple point2 = rotation * point1;
    ASSERT_TRUE(Point(1, -1, 0) == point2);

    Tuple point3 = scale * point2;
    ASSERT_TRUE(Point(5, -5, 0) == point3);

    Tuple point4 = translate * point3;
    ASSERT_TRUE(Point(15, 0, 7) == point4);
}

// Chained transformations must be applied in reverse order
TEST(TransformTests, TestChaining) {
    Point point(1, 0, 1);
    Transform transform1;
    transform1.translate(10, 5, 7);
    transform1.scale(5, 5, 5);
    transform1.rotateX(M_PI_2);

    Transform transform2;
    transform2.translate(10, 5, 7).scale(5, 5, 5).rotateX(M_PI_2);

    ASSERT_TRUE(Point(15, 0, 7) == transform1 * point);
    ASSERT_TRUE(Point(15, 0, 7) == transform2 * point);
}

// A view transformation matrix looking in positive z direction
TEST(TransformTests, TestViewTransformation) {
    Point from(0, 0, 0);
    Point to(0, 0, 1);
    Vector up(0, 1, 0);

    Transform transform = Transform::viewTransform(from, to, up);

    ASSERT_TRUE(Transform::scaling(-1, 1, -1) == transform);
}

// The view transformation moves the world
TEST(TransformTests, TestMovingWorld) {
    Point from(0, 0, 8);
    Point to(0, 0, 0);
    Vector up(0, 1, 0);

    Transform transform = Transform::viewTransform(from, to, up);

    ASSERT_TRUE(Transform::translation(0, 0, -8) == transform);
}

// An arbitrary view transformation
TEST(TransformTests, TestArbitraryTransform) {
    Point from(1, 3, 2);
    Point to(4, -2, 8);
    Vector up(1, 1, 0);

    Transform transform = Transform::viewTransform(from, to, up);

    ASSERT_TRUE(initResultMatrix() == transform);
}

Transform initResultMatrix() {
    Transform result;
    float rowA1[] = {-0.50709, 0.50709, 0.67612, -2.36643};
    float rowA2[] = {0.76772, 0.60609,  0.12122, -2.82843};
    float rowA3[] = {-0.35857, 0.59761, -0.71714,  0.00000};
    float rowA4[] = {0.00000, 0.00000,  0.00000,  1.00000};
    std::copy(rowA1, rowA1 + 4, result[0]);
    std::copy(rowA2, rowA2 + 4, result[1]);
    std::copy(rowA3, rowA3 + 4, result[2]);
    std::copy(rowA4, rowA4 + 4, result[3]);

    return result;
}
