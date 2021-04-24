//
// Created by Max on 2021-01-05.
//

#ifndef RAYTRACER_TRANSFORM_H
#define RAYTRACER_TRANSFORM_H


#include <iostream>
#include "Matrix.h"

class Transform : public Matrix {
public:
    Transform() : Matrix(4, 4) {
        setToIdentityMatrix();
    }

    Transform(const Transform &other) : Matrix(other) {}

    static Transform viewTransform(const Point& from, const Point& to, const Vector& up);

    static Transform translation(double x, double y, double z);

    static Transform scaling(double x, double y, double z);

    static Transform xRotation(double angle);

    static Transform yRotation(double angle);

    static Transform zRotation(double angle);

    static Transform shearing(double xToY, double xToZ, double yToX, double yToZ, double zToX, double zToY);

    Transform &translate(double x, double y, double z);

    Transform &scale(double x, double y, double z);

    Transform &rotateX(double angle);

    Transform &rotateY(double angle);

    Transform &rotateZ(double angle);

    Transform &shear(double xToY, double xToZ, double yToX, double yToZ, double zToX, double zToY);

private:
    Transform &multiplyTransforms(const Transform &other);
};

#endif //RAYTRACER_TRANSFORM_H
