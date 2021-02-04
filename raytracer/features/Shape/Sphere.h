//
// Created by Max on 2021-01-20.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "../Tuple/Point.h"
#include "../Matrix/Matrices.h"
#include "../Material/Material.h"

class Sphere {
public:
    Transform transform;
    Material material;

    Sphere() {}

    Sphere(Point origin) {
        this->origin = origin;
    }

    void setTransform(Transform transform);

    Tuple normalAt(Tuple worldPoint);

    Point origin = Point(0, 0, 0);
};


#endif //RAYTRACER_SPHERE_H
