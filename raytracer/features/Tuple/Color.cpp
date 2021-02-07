//
// Created by Max on 2021-01-02.
//

#include "Color.h"

Color::Color(float red, float green, float blue) {
    this->x = red;
    this->y = green;
    this->z = blue;
    this->w = 0.0;
}

Color &Color::operator=(const Tuple &other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;

    return *this;
}
