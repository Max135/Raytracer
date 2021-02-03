//
// Created by Max on 2021-01-27.
//

#include "gtest/gtest.h"
#include "../raytracer/features/Shape/Shapes.h"

TEST(SphereTests, TestDefaultTransform) {
    Sphere s;

    ASSERT_TRUE(Matrix::identityMatrix() == s.transform);
}

TEST(SphereTests, TestSettingTransform) {
    Sphere s;
    Transform t = Transform::translation(2, 3, 4);
    s.setTransform(t);

    ASSERT_TRUE(t == s.transform);
}
