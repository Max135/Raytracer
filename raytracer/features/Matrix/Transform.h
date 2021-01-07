//
// Created by Max on 2021-01-05.
//

#ifndef RAYTRACER_TRANSFORM_H
#define RAYTRACER_TRANSFORM_H


#include "Matrix.h"

class Transform : public Matrix{
public:
    Transform() : Matrix(4, 4) {
        setToIdentityMatrix();
    }

    static Transform translation(float x, float y, float z);

    static Transform scaling(float x, float y, float z);

    static Transform xRotation(float angle);

    static Transform yRotation(float angle);

    static Transform zRotation(float angle);

    static Transform shearing(float xToY, float xToZ, float yToX, float yToZ, float zToX, float zToY);
};

#endif //RAYTRACER_TRANSFORM_H
