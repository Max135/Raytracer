//
// Created by Max on 2021-01-10.
//

#include "Ray.h"

Tuple Ray::position(float time) {
    return origin + direction * time;
}

std::vector<float> Ray::intersect(Sphere sphere) {
    Tuple sphereToRay = this->origin - sphere.origin;

    float a = this->direction.dot(this->direction);
    float b = 2 * this->direction.dot(sphereToRay);
    float c = sphereToRay.dot(sphereToRay) - 1;

    float discriminant = b * b - 4 * a * c;

    if(discriminant < 0)
        return std::vector<float>();

    float squareRoot = sqrt(discriminant);

    float t1 = (-b - squareRoot) / (2 * a);
    float t2 = (-b + squareRoot) / (2 * a);


    std::vector<float> vector;
    if(t1 > t2) {
        vector.push_back(t2);
        vector.push_back(t1);
    } else {
        vector.push_back(t1);
        vector.push_back(t2);
    }

    return vector;
}
