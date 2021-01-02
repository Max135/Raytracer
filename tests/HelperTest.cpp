//
// Created by Max on 2021-01-01.
//

#include "../raytracer/Helper.h"
#include "gtest/gtest.h"

TEST(HelperTests, TestCompareFloat) {
    float a = 1.1, b = 1.10000000001;
    ASSERT_EQ(true, Helper::compareFloat(a, b));
}