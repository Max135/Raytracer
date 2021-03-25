//
// Created by Max on 2021-01-01.
//

#include "Helper.h"
#include <cmath>

bool Helper::compareFloat(double a, double b) {
//    double i = INFINITY;
    return abs(a - b) < EPSILON;
}

bool Helper::compareFloat(double a, double b, double range) {
    return abs(a - b) < range;
}
