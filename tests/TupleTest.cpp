//
// Created by Max on 2021-01-01.
//

#include "../raytracer/features/Tuple/Tuples.h"
#include "../raytracer/features/Helper.h"
#include "gtest/gtest.h"

// << "x: " << b.x << " y: " << b.y << " z: " << b.z << " w: " << b.w

// A tuple with w=1.0 is a point
TEST(TupleTests, TestPointValues) {
    double x = 4.3, y = -4.2, z = 3.1, w = 1.0;
    Tuple point(x, y, z, w);

    ASSERT_EQ(x, point.x);
    ASSERT_EQ(y, point.y);
    ASSERT_EQ(z, point.z);
    ASSERT_EQ(w, point.w);
    ASSERT_NE(0.0, point.w);
}

// A tuple with w=0.0 is a vector
TEST(TupleTests, TestVectorValues) {
    double x = 4.3, y = -4.2, z = 3.1, w = 0.0;
    Tuple vector(x, y, z, w);

    ASSERT_EQ(x, vector.x);
    ASSERT_EQ(y, vector.y);
    ASSERT_EQ(z, vector.z);
    ASSERT_EQ(w, vector.w);
    ASSERT_NE(1.0, vector.w);
}

// Point() creates tuples with w=1
TEST(TupleTests, TestPointCreation) {
    double x = 4.3, y = -4.2, z = 3.1;
    Vector vector = Vector(x, y, z);
    ASSERT_EQ(0.0, vector.w);
}

// Vector() creates tuples with w=1
TEST(TupleTests, TestVectorCreation) {
    double x = 4.3, y = -4.2, z = 3.1;
    Point point = Point(x, y, z);
    ASSERT_EQ(1.0, point.w);
}

// Round off errors still compare to true
TEST(TupleTests, TestTupleEquation) {
    double x1 = 4.3, y1 = -4.2, z1 = 3.1;
    Point point1 = Point(x1, y1, z1);

    double x2 = 1.0, y2 = 1.0, z2 = 1.0;
    Point point2 = Point(x2, y2, z2);
    Point point3 = Point(x2, y2, z2);
    Vector vector1 = Vector(x2, y2, z2);

    double x3 = 1.00000001, y3 = 1.00000001, z3 = 1.00000001;
    Vector vector2 = Vector(x3, y3, z3);

    ASSERT_FALSE(point1 == point2);
    ASSERT_TRUE(point2 == point3);
    ASSERT_FALSE(point3 == vector1);
    ASSERT_TRUE(vector1 == vector2);
    ASSERT_TRUE(vector1 == vector2);
}

// Adding two tuples
TEST(TupleTests, TestAddTuples) {
    double x1 = 1.0, y1 = -1.0, z1 = 1.0;
    Vector vector = Vector(x1, y1, z1);

    double x2 = 0.5, y2 = 0.5, z2 = 0.5;
    Point point = Point(x2, y2, z2);

    ASSERT_TRUE(Point(1.5, -0.5, 1.5) == (point + vector));
    ASSERT_FALSE(Vector(1.5, -0.5, 1.5) == (vector + point));
    ASSERT_FALSE(Point(2.0, -2.0, 2.0) == (vector + vector));
    ASSERT_TRUE(Vector(2.0, -2.0, 2.0) == (vector + vector));
}

// Subtracting two points, a vector from a point and two vectors
TEST(TupleTests, TestSubstractTuples) {
    double x1 = 3, y1 = 2, z1 = 1;
    Point point1 = Point(x1, y1, z1);
    Vector vector1 = Vector(x1, y1, z1);

    double x2 = 5, y2 = 6, z2 = 7;
    Point point2 = Point(x2, y2, z2);
    Vector vector2 = Vector(x2, y2, z2);

    ASSERT_TRUE(Vector(-2, -4, -6) == point1 - point2);
    ASSERT_TRUE(Point(-2, -4, -6) == point1 - vector2);
    ASSERT_TRUE(Vector(-2, -4, -6) == vector1 - vector2);
}

// Negating a tuple
TEST(TupleTests, TestNegatingTuple) {
    double x1 = 3, y1 = 2, z1 = 1;
    Point point1 = Point(x1, y1, z1);

    double x2 = -3, y2 = 2, z2 = -1;
    Vector vector1 = Vector(x2, y2, z2);

    ASSERT_TRUE(Tuple(-3, -2, -1, -1) == -point1);
    ASSERT_TRUE(Tuple(3, -2, 1, 0) == -vector1);
}

// Multiplying a tuple by a scalar and dividing a tuple by a scalar
TEST(TupleTests, TestScalarOperations) {
    Tuple a = Tuple(1, -2, 3, -4);

    ASSERT_TRUE(Tuple(3.5, -7, 10.5, -14) == a * 3.5);
    ASSERT_TRUE(Tuple(0.5, -1, 1.5, -2) == a * 0.5);
    ASSERT_TRUE(Tuple(0.5, -1, 1.5, -2) == a / 2);
}

// Computing the magnitude of vectors
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

// Normalizing vector(4, 0, 0) gives (1, 0, 0)
TEST(TupleTests, TestNormalization) {
    Vector vector1 = Vector(4, 0, 0);
    ASSERT_TRUE(Vector(1, 0, 0) == vector1.normalize());

    Vector vector2 = Vector(1, 2, 3);
    ASSERT_TRUE(Vector(0.26726, 0.53452, 0.80178) == vector2.normalize());
}

// The magnitude of a normalized vector
TEST(TupleTests, TestMagnitudeNormalized) {
    Vector v(1, 2, 3);
    Tuple norm = v.normalize();

    ASSERT_TRUE(Helper::compareFloat(1, norm.magnitude()));
}

// The dot product of two tuples
TEST(TupleTests, TestDotProduct) {
    Vector vector1 = Vector(1, 2, 3);
    Vector vector2 = Vector(2, 3, 4);

    ASSERT_EQ(20, vector1.dot(vector2));
}

// The cross product of two vectors
TEST(TupleTests, TestCross) {
    Vector vector1 = Vector(1, 2, 3);
    Vector vector2 = Vector(2, 3, 4);

    ASSERT_TRUE(Vector(-1, 2, -1) == vector1.cross(vector2));
    ASSERT_TRUE(Vector(1, -2, 1) == vector2.cross(vector1));
}

// Colors are (red, green, blue) tuples
TEST(TupleTests, TestColorAssignation) {
    Color color = Color(-0.5, 0.4, 1.7);
    ASSERT_EQ(-0.5, color.x);
    ASSERT_EQ(0.4, color.y);
    ASSERT_EQ(1.7, color.z);
//    ASSERT_EQ(-0.5f, color.red);
//    ASSERT_EQ(0.4f, color.green);
//    ASSERT_EQ(1.7f, color.blue);
//    color.red = 1.1;
//    ASSERT_TRUE(Helper::compareFloat(color.red, 1.1));
//    color.x = 0.7;
//    ASSERT_TRUE(Helper::compareFloat(color.red, 0.7));
}

// Adding colors
TEST(TupleTests, TestColorAddition) {
    Color c1 = Color(0.9, 0.6, 0.75);
    Color c2 = Color(0.7, 0.1, 0.25);

    ASSERT_TRUE(Color(1.6, 0.7, 1.0) == c1 + c2);
}

// Subtracting colors
TEST(TupleTests, TestColorSubtraction) {
    Color c1 = Color(0.9, 0.6, 0.75);
    Color c2 = Color(0.7, 0.1, 0.25);

    ASSERT_TRUE(Color(0.2, 0.5, 0.5) == c1 - c2);
}

// Multiplying a color by a scalar
TEST(TupleTests, TestColorMultiplicationScalar) {
    Color color = Color(0.2, 0.3, 0.4);

    ASSERT_TRUE(Color(0.4, 0.6, 0.8) == color * 2);
}

// Multiplying colors
TEST(TupleTests, TestColorMultiplicationColor) {
    Color c1 = Color(1, 0.2, 0.4);
    Color c2 = Color(0.9, 1, 0.1);

    ASSERT_TRUE(Color(0.9, 0.2, 0.04) == (c1 * c2));
}

// Reflecting a vector approaching at 45°
TEST(TupleTests, TestReflectingVector) {
    Vector v(1, -1, 0);
    Vector ground(0, 1, 0);

    Tuple reflection = v.reflectOff(ground);

    ASSERT_TRUE(Vector(1, 1, 0) == reflection);
}

// Reflecting a vector off a slanted surface
TEST(TupleTests, TestReflectingSlanted) {
    Vector v(0, -1, 0);
    Vector ground(sqrt(2)/2.0, sqrt(2)/2.0, 0);

    Tuple reflection = v.reflectOff(ground);

    ASSERT_TRUE(Vector(1, 0, 0) == reflection);
}
