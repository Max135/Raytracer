//
// Created by Max on 2021-01-02.
//

#ifndef RAYTRACER_VECTOR_H
#define RAYTRACER_VECTOR_H


#include "Tuple.h"

class Vector : public Tuple {
public:
    Vector(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = 0.0;
    }
};


#endif //RAYTRACER_VECTOR_H
