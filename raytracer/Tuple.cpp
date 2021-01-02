//
// Created by Max on 2021-01-01.
//

#include <string>
#include "Tuple.h"
#include "Helper.h"

bool Tuple::areEqual(Tuple a, Tuple b) {
    return Helper::compareFloat(a.x, b.x) && Helper::compareFloat(a.y, b.y) && Helper::compareFloat(a.z, b.z) && Helper::compareFloat(a.w, b.w);
}

Tuple Tuple::add(Tuple a, Tuple b) {
    Tuple tuple;

    tuple.x = a.x + b.x;
    tuple.y = a.y + b.y;
    tuple.z = a.z + b.z;
    tuple.w = a.w + b.w;

    return tuple;
}

Tuple Tuple::subtract(Tuple a, Tuple b) {
    Tuple tuple;

    tuple.x = a.x - b.x;
    tuple.y = a.y - b.y;
    tuple.z = a.z - b.z;
    tuple.w = a.w - b.w;

    return tuple;
}

Tuple Tuple::negate(Tuple a) {
    Tuple tuple;

    tuple.x = -a.x;
    tuple.y = -a.y;
    tuple.z = -a.z;
    tuple.w = -a.w;

    return tuple;
}
