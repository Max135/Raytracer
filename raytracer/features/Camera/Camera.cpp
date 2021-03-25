//
// Created by Max on 2021-03-24.
//

#include "Camera.h"

Camera::Camera(int hSize, int vSize, float fov) {
    this->hSize = hSize;
    this->vSize = vSize;
    this->fov = fov;

    calculatePixelSize();
}

void Camera::calculatePixelSize() {
    float halfView = tan(this->fov / 2);
    float aspect = (float) this->hSize / (float) this->vSize;

    this->halfWidth = (aspect >= 1) ? halfView : halfView * aspect;
    this->halfHeight = (aspect >= 1) ? halfView / aspect : halfView;

    this->pixelSize = (this->halfWidth * 2) / (float) this->hSize;
}
