//
// Created by Max on 2021-01-01.
//

#include "../raytracer/Tuple.h"
#include "gtest/gtest.h"

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