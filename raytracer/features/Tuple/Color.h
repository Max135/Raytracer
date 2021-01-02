//
// Created by Max on 2021-01-02.
//

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H


#include "Tuple.h"

class Color: public Tuple {
public:
    //FML
//    float& red = this->x;
//    float& green = this->y;
//    float& blue = this->z;
    Color(float red, float green, float blue) {
        this->x = red;
        this->y = green;
        this->z = blue;
        this->w = 0.0;
    }

    Color() {}

};


#endif //RAYTRACER_COLOR_H
