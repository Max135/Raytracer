//
// Created by Max on 2021-01-10.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include <vector>
#include <iostream>
#include "../Tuple/Tuples.h"
#include "../Shape/Sphere.h"
#include "../Intersection/Junctions.h"
#include "../World/World.h"

class Ray {
public:
    Tuple origin;
    Tuple direction;

    Ray(Point origin, Vector direction) : origin(origin), direction(direction) {}

    Ray(Tuple origin, Tuple direction) : origin(origin), direction(direction) {}

    PreComputation prepareComputations(Intersection intersection);

    Tuple position(float time);

    Intersections intersect(Sphere *sphere);

    Intersections intersect(World *world);

    Ray transform(Matrix *transform);

    std::string toString();

private:
    std::vector<Intersection> intersection(Ray ray, Sphere *sphere);
};


#endif //RAYTRACER_RAY_H
