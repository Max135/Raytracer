//
// Created by Max on 2021-01-20.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include <utility>
#include "../Tuple/Point.h"
#include "../Matrix/Matrices.h"
#include "../Material/Material.h"

class Sphere {
public:
    Transform transform;
    Material material;
    Point origin = Point(0, 0, 0);

    Sphere() {}

    Sphere(Point origin);

    Sphere(Sphere const &other);

    bool operator==(const Sphere &other);

    void setTransform(Transform transform);

    Tuple normalAt(const Tuple &worldPoint);

    std::string toString();
};


#endif //RAYTRACER_SPHERE_H
