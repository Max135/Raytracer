//
// Created by Max on 2021-01-20.
//

#include "Sphere.h"

void Sphere::setTransform(Transform transform) {
    this->transform = transform;
}

Tuple Sphere::normalAt(const Tuple& worldPoint) {
    Tuple objectPoint = this->transform.inverse() * worldPoint;
    Tuple objectNormal = objectPoint - Point(0, 0, 0);
    Tuple worldNormal = this->transform.inverse().transpose() * objectNormal;
    worldNormal.w = 0.0;

    return worldNormal.normalize();
}

std::string Sphere::toString() {
    std::string string;
    string.append("\nTransform: ");
    string.append(this->transform.toString());
    string.append("Origin: ");
    string.append(this->origin.toString());
    string.append("\nMaterial: ");
    string.append(this->material.toString());
    string.append("\n");

    return string;
}
