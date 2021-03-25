//
// Created by Max on 2021-03-24.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include "../Matrix/Transform.h"
#include "../Ray/Ray.h"
#include "../Canvas/Canvas.h"

class Camera {
public:
    Camera(int hSize, int vSize, float fov);

    int hSize;
    int vSize;
    float fov;
    float pixelSize;
    Transform transform;

    Ray rayForPixel(int px, int py);

    Canvas render(const World& world);

private:
    float halfWidth;
    float halfHeight;

    void calculatePixelSize();
};


#endif //RAYTRACER_CAMERA_H
