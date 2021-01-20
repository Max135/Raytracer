//
// Created by Max on 2021-01-20.
//

#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H


#include "../Shape/Sphere.h"

class Intersection {
public:
    Intersection(float t, Sphere* sphere): t(t), sphere(sphere) {}

    static std::vector<Intersection> intersections(Intersection a, Intersection b);

    float t;
    Sphere* sphere;
};


#endif //RAYTRACER_INTERSECTION_H
