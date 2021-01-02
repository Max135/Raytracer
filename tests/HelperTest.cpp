//
// Created by Max on 2021-01-01.
//

#include "../raytracer/features/Helper.h"
#include "gtest/gtest.h"

TEST(HelperTests, TestCompareFloat) {
    ASSERT_TRUE(Helper::compareFloat(1.1, 1.10000000001));
    ASSERT_FALSE(Helper::compareFloat(1.1, 1.2));
    ASSERT_TRUE(Helper::compareFloat(1, 1));
    ASSERT_FALSE(Helper::compareFloat(1, 2));
}