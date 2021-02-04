//
// Created by Max on 2021-02-03.
//

#include "../raytracer/features/Material/Material.h"
#include "gtest/gtest.h"
#include "../raytracer/features/Light/Light.h"

TEST(MaterialTests, TestDefaultMaterial) {
    Material mat;

    ASSERT_TRUE(Color(1, 1, 1) == mat.color);
    ASSERT_TRUE(Helper::compareFloat(mat.ambient, 0.1));
    ASSERT_TRUE(Helper::compareFloat(mat.diffuse, 0.9));
    ASSERT_TRUE(Helper::compareFloat(mat.specular, 0.9));
    ASSERT_TRUE(Helper::compareFloat(mat.shininess, 200.0));
}

TEST(MaterialTests, TestEyeBetween) {
    Material m;
    Point position(0, 0, 0);
    Vector eyeV(0, 0, -1);
    Vector normalV(0, 0, -1);
    Light light(Point(0, 0, -10), Color(1, 1, 1));

    Tuple result = m.lighting(light, position, eyeV, normalV);

    ASSERT_TRUE(Color(1.9, 1.9, 1.9) == result);
}

TEST(MaterialTests, TestEyeBetweenOffset45) {
    Material m;
    Point position(0, 0, 0);
    Vector eyeV(0, sqrt(2)/2.0, -sqrt(2)/2.0);
    Vector normalV(0, 0, -1);
    Light light(Point(0, 0, -10), Color(1, 1, 1));

    Tuple result = m.lighting(light, position, eyeV, normalV);

    ASSERT_TRUE(Color(1.0, 1.0, 1.0) == result);
}

TEST(MaterialTests, TestEyeBetweenLightOffset45) {
    Material m;
    Point position(0, 0, 0);
    Vector eyeV(0, 0, -1);
    Vector normalV(0, 0, -1);
    Light light(Point(0, 10, -10), Color(1, 1, 1));

    Tuple result = m.lighting(light, position, eyeV, normalV);

    ASSERT_TRUE(Color(0.7364, 0.7364, 0.7364) == result);
}

TEST(MaterialTests, TestEyeReflectionPath) {
    Material m;
    Point position(0, 0, 0);
    Vector eyeV(0, -sqrt(2)/2.0, -sqrt(2)/2.0);
    Vector normalV(0, 0, -1);
    Light light(Point(0, 10, -10), Color(1, 1, 1));

    Tuple result = m.lighting(light, position, eyeV, normalV);

    ASSERT_TRUE(Color(1.63639, 1.63639, 1.63639) == result) << result.toString();
}

TEST(MaterialTests, TestEyeBehindSurface) {
    Material m;
    Point position(0, 0, 0);
    Vector eyeV(0, 0, -1);
    Vector normalV(0, 0, -1);
    Light light(Point(0, 0, 10), Color(1, 1, 1));

    Tuple result = m.lighting(light, position, eyeV, normalV);

    ASSERT_TRUE(Color(0.1, 0.1, 0.1) == result);
}
