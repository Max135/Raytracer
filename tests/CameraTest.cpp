//
// Created by Max on 2021-03-24.
//

#include "../raytracer/features/Camera/Camera.h"
#include "gtest/gtest.h"

// Constructing a camera
TEST(CameraTests, TestConstructingCamera) {
    int hsize = 160;
    int vsize = 120;
    float fov = M_PI_2;

    Camera camera(hsize, vsize, fov);

    ASSERT_EQ(hsize, camera.hSize);
    ASSERT_EQ(vsize, camera.vSize);
    ASSERT_EQ(fov, camera.fov);
    ASSERT_TRUE(Transform::identityMatrix() == camera.transform);
}

// The pixel size for a horizontal canvas
TEST(CameraTests, TestPixelSizeHorizontal) {
    Camera camera(200, 125, M_PI_2);

    ASSERT_TRUE(Helper::compareFloat(0.01, camera.pixelSize));
}

// The pixel size for a vertical canvas
TEST(CameraTests, TestPixelSizeVertical) {
    Camera camera(125, 200, M_PI_2);

    ASSERT_TRUE(Helper::compareFloat(0.01, camera.pixelSize));
}
