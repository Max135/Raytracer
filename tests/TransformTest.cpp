//
// Created by Max on 2021-01-05.
//

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
