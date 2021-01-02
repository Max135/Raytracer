//
// Created by Max on 2021-01-01.
//

#ifndef RAYTRACER_TUPLE_H
#define RAYTRACER_TUPLE_H


class Tuple {
public:
    float x, y, z, w;

    Tuple() {}

    Tuple(float x, float y, float z, float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    static Tuple point(float x, float y, float z) {
        return Tuple(x, y, z, 1.0);
    }

    static Tuple vector(float x, float y, float z) {
        return Tuple(x, y, z, 0.0);
    }
};

#endif //RAYTRACER_TUPLE_H
