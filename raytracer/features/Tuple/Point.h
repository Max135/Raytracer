//
// Created by Max on 2021-01-02.
//

#ifndef RAYTRACER_POINT_H
#define RAYTRACER_POINT_H


#include "Tuple.h"

class Point : public Tuple {
public:
    Point() {}

    Point(float x, float y, float z);
};


#endif //RAYTRACER_POINT_H
