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

    Light() {
        intensity = Color();
        position = Point();
    }

    Light(Point position, Color intensity) : position(std::move(position)), intensity(std::move(intensity)) {}

    bool operator==(const Light & other) {
        return this->position == other.position && this->intensity == other.intensity;
    }

    Light& operator=(const Light & other) {
        if(this == &other)
            return *this;

        this->intensity = other.intensity;
        this->position = other.position;
        return *this;
    }
};


#endif //RAYTRACER_LIGHT_H
