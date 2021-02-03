//
// Created by Max on 2021-01-10.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include <vector>
#include "../Tuple/Point.h"
#include "../Tuple/Vector.h"
#include "../Shape/Sphere.h"
#include "../Intersection/Intersection.h"
#include "../Matrix/Matrices.h"

class Ray {

public:
    Tuple origin;
    Tuple direction;

    Ray(Point origin, Vector direction) : origin(origin), direction(direction) {}

    Ray(Tuple origin, Tuple direction) : origin(origin), direction(direction) {}

    Tuple position(float time);

    std::vector<Intersection> intersect(Sphere *sphere);

    Ray transform(Matrix *transform);

private:
    std::vector<Intersection> intersection(Ray ray, Sphere *sphere);
};


#endif //RAYTRACER_RAY_H
