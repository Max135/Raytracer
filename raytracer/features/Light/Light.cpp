//
// Created by Max on 2021-02-03.
//

#include "Light.h"

Light::Light() {
    intensity = Color();
    position = Point();
}

bool Light::operator==(const Light &other) {
    return this->position == other.position && this->intensity == other.intensity;
}

Light &Light::operator=(const Light &other) {
    if(this == &other)
        return *this;

    this->intensity = other.intensity;
    this->position = other.position;
    return *this;
}
