//
// Created by Max on 2021-01-01.
//

#include "../raytracer/Tuple.h"
#include "../raytracer/Helper.h"
#include "gtest/gtest.h"

// << "x: " << b.x << " y: " << b.y << " z: " << b.z << " w: " << b.w

TEST(TupleTests, TestTupleValues) {
    float x = 4.3, y = -4.2, z = 3.1, w = 1.0;
    Tuple point(x, y, z, w);
    ASSERT_EQ(x, point.x);
    ASSERT_EQ(y, point.y);
    ASSERT_EQ(z, point.z);
    ASSERT_EQ(w, point.w);
    ASSERT_NE(0.0, point.w);

    w = 0.0;
    Tuple vector(x, y, z, w);
    ASSERT_EQ(x, vector.x);
    ASSERT_EQ(y, vector.y);
    ASSERT_EQ(z, vector.z);
    ASSERT_EQ(w, vector.w);
    ASSERT_NE(1.0, vector.w);
}

TEST(TupleTests, TestTupleCreation) {
    float x = 4.3, y = -4.2, z = 3.1;
    Tuple vector = Tuple::vector(x, y, z);
    ASSERT_EQ(0.0, vector.w);

    Tuple point = Tuple::point(x, y, z);
    ASSERT_EQ(1.0, point.w);
}

TEST(TupleTests, TestTupleEquation) {
    float x1 = 4.3, y1 = -4.2, z1 = 3.1;
    Tuple point1 = Tuple::point(x1, y1, z1);

    float x2 = 1.0, y2 = 1.0, z2 = 1.0;
    Tuple point2 = Tuple::point(x2, y2, z2);
    Tuple point3 = Tuple::point(x2, y2, z2);

    float x3 = 1.00000001, y3 = 1.00000001, z3 = 1.00000001;
    Tuple vector1 = Tuple::vector(x2, y2, z2);
    Tuple vector2 = Tuple::vector(x3, y3, z3);

    ASSERT_FALSE(point1 == point2);
    ASSERT_TRUE(point2 == point3);
    ASSERT_FALSE(point3 == vector1);
    ASSERT_TRUE(vector1 == vector2);
    ASSERT_TRUE(vector1 == vector2);
}

TEST(TupleTests, TestAddTuples) {
    float x1 = 1.0, y1 = -1.0, z1 = 1.0;
    Tuple vector = Tuple::vector(x1, y1, z1);

    float x2 = 0.5, y2 = 0.5, z2 = 0.5;
    Tuple point = Tuple::point(x2, y2, z2);

    ASSERT_TRUE(Tuple::point(1.5, -0.5, 1.5) == (point + vector));
    ASSERT_FALSE(Tuple::vector(1.5, -0.5, 1.5) == (vector + point));
    ASSERT_FALSE(Tuple::point(2.0, -2.0, 2.0) == (vector + vector));
    ASSERT_TRUE(Tuple::vector(2.0, -2.0, 2.0) == (vector + vector));
}

TEST(TupleTests, TestSubstractTuples) {
    float x1 = 3, y1 = 2, z1 = 1;
    Tuple point1 = Tuple::point(x1, y1, z1);
    Tuple vector1 = Tuple::vector(x1, y1, z1);

    float x2 = 5, y2 = 6, z2 = 7;
    Tuple point2 = Tuple::point(x2, y2, z2);
    Tuple vector2 = Tuple::vector(x2, y2, z2);

    ASSERT_TRUE(Tuple::vector(-2, -4, -6) == point1 - point2);
    ASSERT_TRUE(Tuple::point(-2, -4, -6) == point1 - vector2);
    ASSERT_TRUE(Tuple::vector(-2, -4, -6) == vector1 - vector2);
}

TEST(TupleTests, TestNegatingTuple) {
    float x1 = 3, y1 = 2, z1 = 1;
    Tuple point1 = Tuple::point(x1, y1, z1);

    float x2 = -3, y2 = 2, z2 = -1;
    Tuple vector1 = Tuple::vector(x2, y2, z2);

    ASSERT_TRUE(Tuple(-3, -2, -1, -1) == -point1);
    ASSERT_TRUE(Tuple(3, -2, 1, 0) == -vector1);
}

TEST(TupleTests, TestScalarOperations) {
    Tuple a = Tuple(1, -2, 3, -4);

    ASSERT_TRUE(Tuple(3.5, -7, 10.5, -14) == a * 3.5);
    ASSERT_TRUE(Tuple(0.5, -1, 1.5, -2) == a * 0.5);
    ASSERT_TRUE(Tuple(0.5, -1, 1.5, -2) == a / 2);
}

TEST(TupleTests, TestMagnitude) {
    Tuple vector1 = Tuple::vector(1, 0, 0);
    Tuple vector2 = Tuple::vector(0, 1, 0);
    Tuple vector3 = Tuple::vector(0, 0, 1);
    Tuple vector4 = Tuple::vector(1, 2, 3);
    Tuple vector5 = Tuple::vector(-1, -2, -3);

    ASSERT_EQ(1, vector1.magnitude());
    ASSERT_EQ(1, vector2.magnitude());
    ASSERT_EQ(1, vector3.magnitude());

    ASSERT_TRUE(Helper::compareFloat(sqrt(14), vector4.magnitude()));
    ASSERT_TRUE(Helper::compareFloat(sqrt(14), vector5.magnitude()));
}