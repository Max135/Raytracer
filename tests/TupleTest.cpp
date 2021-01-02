//
// Created by Max on 2021-01-01.
//

#include "../raytracer/features/Tuple/Tuples.h"
#include "../raytracer/features/Helper.h"
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
    Vector vector = Vector(x, y, z);
    ASSERT_EQ(0.0, vector.w);

    Point point = Point(x, y, z);
    ASSERT_EQ(1.0, point.w);
}

TEST(TupleTests, TestTupleEquation) {
    float x1 = 4.3, y1 = -4.2, z1 = 3.1;
    Point point1 = Point(x1, y1, z1);

    float x2 = 1.0, y2 = 1.0, z2 = 1.0;
    Point point2 = Point(x2, y2, z2);
    Point point3 = Point(x2, y2, z2);

    float x3 = 1.00000001, y3 = 1.00000001, z3 = 1.00000001;
    Vector vector1 = Vector(x2, y2, z2);
    Vector vector2 = Vector(x3, y3, z3);

    ASSERT_FALSE(point1 == point2);
    ASSERT_TRUE(point2 == point3);
    ASSERT_FALSE(point3 == vector1);
    ASSERT_TRUE(vector1 == vector2);
    ASSERT_TRUE(vector1 == vector2);
}

TEST(TupleTests, TestAddTuples) {
    float x1 = 1.0, y1 = -1.0, z1 = 1.0;
    Vector vector = Vector(x1, y1, z1);

    float x2 = 0.5, y2 = 0.5, z2 = 0.5;
    Point point = Point(x2, y2, z2);

    ASSERT_TRUE(Point(1.5, -0.5, 1.5) == (point + vector));
    ASSERT_FALSE(Vector(1.5, -0.5, 1.5) == (vector + point));
    ASSERT_FALSE(Point(2.0, -2.0, 2.0) == (vector + vector));
    ASSERT_TRUE(Vector(2.0, -2.0, 2.0) == (vector + vector));
}

TEST(TupleTests, TestSubstractTuples) {
    float x1 = 3, y1 = 2, z1 = 1;
    Point point1 = Point(x1, y1, z1);
    Vector vector1 = Vector(x1, y1, z1);

    float x2 = 5, y2 = 6, z2 = 7;
    Point point2 = Point(x2, y2, z2);
    Vector vector2 = Vector(x2, y2, z2);

    ASSERT_TRUE(Vector(-2, -4, -6) == point1 - point2);
    ASSERT_TRUE(Point(-2, -4, -6) == point1 - vector2);
    ASSERT_TRUE(Vector(-2, -4, -6) == vector1 - vector2);
}

TEST(TupleTests, TestNegatingTuple) {
    float x1 = 3, y1 = 2, z1 = 1;
    Point point1 = Point(x1, y1, z1);

    float x2 = -3, y2 = 2, z2 = -1;
    Vector vector1 = Vector(x2, y2, z2);

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
    Vector vector1 = Vector(1, 0, 0);
    Vector vector2 = Vector(0, 1, 0);
    Vector vector3 = Vector(0, 0, 1);
    Vector vector4 = Vector(1, 2, 3);
    Vector vector5 = Vector(-1, -2, -3);

    ASSERT_EQ(1, vector1.magnitude());
    ASSERT_EQ(1, vector2.magnitude());
    ASSERT_EQ(1, vector3.magnitude());

    ASSERT_TRUE(Helper::compareFloat(sqrt(14), vector4.magnitude()));
    ASSERT_TRUE(Helper::compareFloat(sqrt(14), vector5.magnitude()));
}

TEST(TupleTests, TestNormalization) {
    Vector vector1 = Vector(4, 0, 0);
    ASSERT_TRUE(Vector(1, 0, 0) == vector1.preciseNormalize());

    Vector vector2 = Vector(1, 2, 3);
    ASSERT_TRUE(Vector(0.26726, 0.53452, 0.80178) == vector2.preciseNormalize());
}

TEST(TupleTests, TestDotProduct) {
    Vector vector1 = Vector(1, 2, 3);
    Vector vector2 = Vector(2, 3, 4);

    ASSERT_EQ(20, vector1 * vector2);
}

TEST(TupleTests, TestCross) {
    Vector vector1 = Vector(1, 2, 3);
    Vector vector2 = Vector(2, 3, 4);

    ASSERT_TRUE(Vector(-1, 2, -1) == vector1.cross(vector2));
    ASSERT_TRUE(Vector(1, -2, 1) == vector2.cross(vector1));
}

TEST(TupleTests, TestColor) {
    Color color = Color(-0.5, 0.4, 1.7);
    ASSERT_EQ(-0.5f, color.red);
    ASSERT_EQ(0.4f, color.green);
    ASSERT_EQ(1.7f, color.blue);
    color.red = 1.1;
    ASSERT_TRUE(Helper::compareFloat(color.red, 1.1));
    color.x = 0.7;
    ASSERT_TRUE(Helper::compareFloat(color.red, 0.7));
}