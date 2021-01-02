//
// Created by Max on 2021-01-02.
//

#include "../raytracer/features/Canvas/Canvas.h"
#include "gtest/gtest.h"

TEST(CanvasTests, TestCanvasCreation) {
    Canvas canvas(10, 20);

    ASSERT_EQ(10, canvas.width);
    ASSERT_EQ(20, canvas.height);
}
