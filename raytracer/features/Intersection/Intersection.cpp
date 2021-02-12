//
// Created by Max on 2021-01-20.
//

#include "Intersection.h"

Intersection::Intersection() {
    this->t = 0;
    this->sphere = nullptr;
}

bool Intersection::operator==(const Intersection &other) const {
    return (this->t == other.t && this->sphere == other.sphere);
}

std::string Intersection::toString() {
    std::string string;
    string.append(this->sphere->toString());
    string.append("  t: ");
    string.append(std::to_string(t));
    return string;
}
