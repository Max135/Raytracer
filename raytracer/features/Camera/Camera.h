//
// Created by Max on 2021-03-24.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include <thread>
#include "../Matrix/Transform.h"
#include "../Ray/Ray.h"
#include "../Canvas/Canvas.h"

class Camera {
public:
    Camera(int hSize, int vSize, double fov);

    int hSize;
    int vSize;
    double fov;
    double pixelSize;
    Transform transform;

    Ray rayForPixel(int px, int py);

    Canvas render(World *world);

    Canvas multiThreadRender(World *world, int nbThreads = 10);

private:
    double halfWidth;
    double halfHeight;

    void calculatePixelSize();

    void renderPixelRow(int y, Canvas *canvas, World *world);
};


#endif //RAYTRACER_CAMERA_H
