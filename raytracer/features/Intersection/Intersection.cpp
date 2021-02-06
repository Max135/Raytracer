//
// Created by Max on 2021-01-20.
//

#include "Intersection.h"

bool Intersection::operator==(const Intersection &other) const {
    return (this->t == other.t && this->sphere == other.sphere);
}
