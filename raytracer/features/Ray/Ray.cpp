//
// Created by Max on 2021-01-10.
//

#include "Ray.h"
#include <iostream>

Tuple Ray::position(float time) {
    return origin + direction * time;
}

std::vector<Intersection> Ray::intersect(Sphere *sphere) {
    Matrix t = sphere->transform.inverse();
    return intersection(this->transform(&t), sphere);
}

Ray Ray::transform(Matrix *transform) {
    Ray ray(*transform * this->origin, *transform * this->direction);
    return ray;
}

std::vector<Intersection> Ray::intersection(Ray ray, Sphere *sphere) {
    Tuple sphereToRay = ray.origin - sphere->origin;

    float a = ray.direction.dot(ray.direction);
    float b = 2 * ray.direction.dot(sphereToRay);
    float c = sphereToRay.dot(sphereToRay) - 1;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return std::vector<Intersection>();

    float squareRoot = sqrt(discriminant);

    float t1 = (-b - squareRoot) / (2 * a);
    float t2 = (-b + squareRoot) / (2 * a);


    std::vector<Intersection> vector;
    if (t1 > t2) {
        vector.emplace_back(t2, sphere);
        vector.emplace_back(t1, sphere);
    } else {
        vector.emplace_back(t1, sphere);
        vector.emplace_back(t2, sphere);
    }

    return vector;
}

std::string Ray::toString() {
    std::string string;
    string.append("Origin: ");
    string.append(this->origin.toString());
    string.append(" Direction: ");
    string.append(this->direction.toString());
    return string;
}

