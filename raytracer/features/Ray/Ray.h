//
// Created by Max on 2021-01-10.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include <vector>
#include "../Tuple/Point.h"
#include "../Tuple/Vector.h"
#include "../Shape/Sphere.h"
#include "../Intersection/Junctions.h"
#include "../Matrix/Matrices.h"
#include "../World/World.h"

struct preComps {
    float t;
    Sphere *object;
    Tuple point, eyeV, normalV;
    bool inside;
};

class Ray {
public:
    Tuple origin;
    Tuple direction;

    Ray(Point origin, Vector direction) : origin(origin), direction(direction) {}

    Ray(Tuple origin, Tuple direction) : origin(origin), direction(direction) {}

    preComps prepareComputations(Intersection ray);

    Tuple position(float time);

    Intersections intersect(Sphere *sphere);

    Intersections intersect(World *world);

    Ray transform(Matrix *transform);

    std::string toString();

private:
    std::vector<Intersection> intersection(Ray ray, Sphere *sphere);
};


#endif //RAYTRACER_RAY_H
