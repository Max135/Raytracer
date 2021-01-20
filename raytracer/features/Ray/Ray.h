//
// Created by Max on 2021-01-10.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include <vector>
#include "../Tuple/Point.h"
#include "../Tuple/Vector.h"
#include "../Shape/Sphere.h"

class Ray {

public:
    Point origin;
    Vector direction;

    Ray(Point origin, Vector direction) : origin(origin), direction(direction) {}

    Tuple position(float time);

    std::vector<float> intersect(Sphere sphere);
};


#endif //RAYTRACER_RAY_H
