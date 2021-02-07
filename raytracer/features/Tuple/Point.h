//
// Created by Max on 2021-01-02.
//

#ifndef RAYTRACER_POINT_H
#define RAYTRACER_POINT_H


#include "Tuple.h"

class Point : public Tuple {
public:
    Point() {}

    Point(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = 1.0;
    }
};


#endif //RAYTRACER_POINT_H
