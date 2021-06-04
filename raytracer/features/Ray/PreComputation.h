//
// Created by Max on 2021-02-11.
//

#ifndef RAYTRACER_PRECOMPUTATION_H
#define RAYTRACER_PRECOMPUTATION_H


#include "../Shape/Sphere.h"

class PreComputation {
public:
    double t;
    Sphere *object;
    Tuple point, overPoint, eyeV, normalV;
    bool inside;
};


#endif //RAYTRACER_PRECOMPUTATION_H
