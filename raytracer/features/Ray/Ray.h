//
// Created by Max on 2021-01-10.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include "../Tuple/Point.h"
#include "../Tuple/Vector.h"

class Ray {

public:
    Point origin;
    Vector direction;

    Ray(Point origin, Vector direction) : origin(origin), direction(direction) {}

    Tuple position(float time);
};


#endif //RAYTRACER_RAY_H
