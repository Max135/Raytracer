//
// Created by Max on 2021-01-20.
//

#include <vector>
#include "Intersection.h"

std::vector<Intersection> Intersection::intersections(Intersection a, Intersection b) {
    std::vector<Intersection> vector;

    vector.push_back(a);
    vector.push_back(b);

    return vector;
}
