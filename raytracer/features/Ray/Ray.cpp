//
// Created by Max on 2021-01-10.
//

#include "Ray.h"

Tuple Ray::position(float time) {
    return origin + direction * time;
}
