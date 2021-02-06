//
// Created by Max on 2021-01-20.
//

#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H

#include <vector>
#include "../Shape/Sphere.h"

class Intersection {
public:
    float t;
    Sphere *sphere;

    Intersection(float t, Sphere *sphere) : t(t), sphere(sphere) {}

    Intersection() {
        t = 0;
        sphere = nullptr;
    }

    bool operator==(const Intersection &other) const;
};


#endif //RAYTRACER_INTERSECTION_H
