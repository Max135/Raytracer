//
// Created by Max on 2021-01-02.
//

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H


#include "Tuple.h"

class Color : public Tuple {
public:
    //FML
//    double& red = this->x;
//    double& green = this->y;
//    double& blue = this->z;
    Color(double red, double green, double blue);

    Color() {}

    Color &operator=(const Tuple &other);

    static Color black() {
        return Color(0, 0, 0);
    }

    static Color white() {
        return Color(1, 1, 1);
    }

};


#endif //RAYTRACER_COLOR_H
