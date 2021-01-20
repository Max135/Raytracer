//
// Created by Max on 2021-01-10.
//

#include "Ray.h"

Tuple Ray::position(float time) {
    return origin + direction * time;
}

std::vector<Intersection> Ray::intersect(Sphere sphere) {
    Tuple sphereToRay = this->origin - sphere.origin;

    float a = this->direction.dot(this->direction);
    float b = 2 * this->direction.dot(sphereToRay);
    float c = sphereToRay.dot(sphereToRay) - 1;

    float discriminant = b * b - 4 * a * c;

    if(discriminant < 0)
        return std::vector<Intersection>();

    float squareRoot = sqrt(discriminant);

    float t1 = (-b - squareRoot) / (2 * a);
    float t2 = (-b + squareRoot) / (2 * a);


    std::vector<Intersection> vector;
    if(t1 > t2) {
        vector.emplace_back(t2, &sphere);
        vector.emplace_back(t1, &sphere);
    } else {
        vector.emplace_back(t1, &sphere);
        vector.emplace_back(t2, &sphere);
    }

    return vector;
}
