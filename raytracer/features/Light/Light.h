//
// Created by Max on 2021-02-03.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include <utility>
#include "../Tuple/Tuples.h"

class Light {
public:
    Color intensity;
    Point position;

    Light();

    Light(Point position, Color intensity) : position(std::move(position)), intensity(std::move(intensity)) {}

    bool operator==(const Light &other);

    Light &operator=(const Light &other);
};


#endif //RAYTRACER_LIGHT_H
