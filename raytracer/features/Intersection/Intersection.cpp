//
// Created by Max on 2021-01-20.
//

#include "Intersection.h"

bool Intersection::operator==(const Intersection &other) {
    return (this->t == other.t && this->sphere == other.sphere);
}

Intersection Intersection::hit(const std::vector<Intersection>& vector) {
    for (Intersection i : vector) {
        if (i.t >= 0) return i;
    }

    return {};
}
