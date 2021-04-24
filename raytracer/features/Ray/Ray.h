//
// Created by Max on 2021-01-10.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include <utility>
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

    Ray(const Point& origin, const Vector& direction) : origin(origin), direction(direction) {}

    Ray(const Tuple& origin, const Tuple& direction) : origin(origin), direction(direction) {}

    PreComputation prepareComputations(const Intersection &intersection) const;

    Tuple position(double time) const;

    Intersections intersect(Sphere *sphere);

    Intersections intersect(World *world);

    Tuple colorAt(World world);

    Ray transform(Matrix *transform) const;

    std::string toString() const;

private:
    std::vector<Intersection> intersection(const Ray& ray, Sphere *sphere);
};


#endif //RAYTRACER_RAY_H
