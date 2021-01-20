//
// Created by Max on 2021-01-20.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "../Tuple/Point.h"

class Sphere {
public:
    Sphere() {}

    Sphere(Point origin) {
        this->origin = origin;
    }

    Point origin = Point(0, 0, 0);
};


#endif //RAYTRACER_SPHERE_H
