//
// Created by Max on 2021-03-24.
//

#include "../raytracer/features/Camera/Camera.h"
#include "gtest/gtest.h"
#include "../raytracer/features/Ray/Ray.h"
#include "../raytracer/features/Canvas/Canvas.h"

// Constructing a camera
TEST(CameraTests, TestConstructingCamera) {
    int hsize = 160;
    int vsize = 120;
    double fov = M_PI_2;

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

// Constructing a ray through the center of the canvas
TEST(CameraTests, TestContructionRayCenter) {
    Camera camera(201, 101, M_PI_2);
    Ray ray = camera.rayForPixel(100, 50);

    ASSERT_TRUE(Point(0, 0, 0) == ray.origin);
    ASSERT_TRUE(Vector(0, 0, -1) == ray.direction);
}

// Constructing a ray through a corner of the canvas
TEST(CameraTests, TestContructionRayCorner) {
    Camera camera(201, 101, M_PI_2);
    Ray ray = camera.rayForPixel(0, 0);

    ASSERT_TRUE(Point(0, 0, 0) == ray.origin);
    ASSERT_TRUE(Vector(0.66519, 0.33259, -0.66851) == ray.direction);
}

// Constructing a ray when the camera is transformed
TEST(CameraTests, TestContructionRayTransformed) {
    Camera camera(201, 101, M_PI_2);
    camera.transform.rotateY(M_PI_4).translate(0, -2, 5);
    Ray ray = camera.rayForPixel(100, 50);

    ASSERT_TRUE(Point(0, 2, -5) == ray.origin);
    ASSERT_TRUE(Vector(sqrt(2)/2, 0, -sqrt(2)/2) == ray.direction);
}

// Rendering a world with a camera
TEST(CameraTests, TestRenderingWorld) {
    World world = World::defaultWorld();
    Camera camera(11, 11, M_PI_2);
    Point from(0, 0, -5);
    Point to(0, 0, 0);
    Vector up(0, 1, 0);

    camera.transform = Transform::viewTransform(from, to, up);
    Canvas image = camera.render(&world);
    Canvas imageMultiThread = camera.multiThreadRender(&world);

    ASSERT_TRUE(Color(0.38066, 0.47583, 0.2855) == image.pixelAt(5, 5));
    ASSERT_TRUE(Color(0.38066, 0.47583, 0.2855) == imageMultiThread.pixelAt(5, 5));
}
