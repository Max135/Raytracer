//
// Created by Max on 2021-01-01.
//

#include "Helper.h"
#include <cmath>

bool Helper::compareFloat(float a, float b) {
    return abs(a - b) < EPSILON;
}
