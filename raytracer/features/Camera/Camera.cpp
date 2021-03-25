//
// Created by Max on 2021-03-24.
//

#include "Camera.h"

Camera::Camera(int hSize, int vSize, double fov) {
    this->hSize = hSize;
    this->vSize = vSize;
    this->fov = fov;

    calculatePixelSize();
}

void Camera::calculatePixelSize() {
    double halfView = tan(this->fov / 2);
    double aspect = (double) this->hSize / (double) this->vSize;

    this->halfWidth = (aspect >= 1) ? halfView : halfView * aspect;
    this->halfHeight = (aspect >= 1) ? halfView / aspect : halfView;

    this->pixelSize = (this->halfWidth * 2) / (double) this->hSize;
}

Ray Camera::rayForPixel(int px, int py) {
    // the offset from the edge of the canvas to the pixel's center
    double xOffset = (px + 0.5) * this->pixelSize;
    double yOffset = (py + 0.5) * this->pixelSize;

    // the untransformed coordinates of the pixel in world space.
    // the camera looks toward -z, so +x is to the left
    double worldX = this->halfWidth - xOffset;
    double worldY = this->halfHeight - yOffset;

    // using the camera matrix, transform the canvas point and the origin,
    // and then compute the ray's direction vector.
    // (canvas is at z = -1)
    Matrix cameraTransformInverse = this->transform.inverse();

    Tuple pixel = cameraTransformInverse * Point(worldX, worldY, -1);
    Tuple origin = cameraTransformInverse * Point(0, 0, 0);
    Tuple direction = (pixel - origin).normalize();

    return Ray(origin, direction);
}

//TODO: Implement multithreading
Canvas Camera::render(const World& world) {
    Canvas canvas(this->hSize, this->vSize);

    for (int y = 0; y < this->vSize; ++y) {
        for (int x = 0; x < this->hSize; ++x) {
            Ray ray = this->rayForPixel(x, y);
            Tuple color = ray.colorAt(world);
            canvas.writePixel(x, y, color);
        }
    }

    return canvas;
}
