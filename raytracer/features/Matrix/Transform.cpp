//
// Created by Max on 2021-01-05.
//

#include "Transform.h"

Transform Transform::viewTransform(Point from, Point to, Vector up) {
    Tuple forward = (to - from).normalize();
    Tuple left = forward.cross(up.normalize());
    Tuple trueUp = left.cross(forward);

    Transform orientation;

    orientation.matrix[0][0] = left.x;
    orientation.matrix[0][1] = left.y;
    orientation.matrix[0][2] = left.z;

    orientation.matrix[1][0] = trueUp.x;
    orientation.matrix[1][1] = trueUp.y;
    orientation.matrix[1][2] = trueUp.z;

    orientation.matrix[2][0] = -forward.x;
    orientation.matrix[2][1] = -forward.y;
    orientation.matrix[2][2] = -forward.z;

    return orientation.translate(-from.x, -from.y, -from.z);
}

Transform Transform::translation(double x, double y, double z) {
    Transform transform;

    transform.matrix[0][3] = x;
    transform.matrix[1][3] = y;
    transform.matrix[2][3] = z;

    return transform;
}

Transform Transform::scaling(double x, double y, double z) {
    Transform transform;

    transform.matrix[0][0] = x;
    transform.matrix[1][1] = y;
    transform.matrix[2][2] = z;

    return transform;
}

Transform Transform::xRotation(double angle) {
    Transform transform;

    double cosine = cos(angle);
    double sine = sin(angle);

    transform.matrix[1][1] = cosine;
    transform.matrix[1][2] = -sine;
    transform.matrix[2][1] = sine;
    transform.matrix[2][2] = cosine;

    return transform;
}

Transform Transform::yRotation(double angle) {
    Transform transform;

    double cosine = cos(angle);
    double sine = sin(angle);

    transform.matrix[0][0] = cosine;
    transform.matrix[0][2] = sine;
    transform.matrix[2][0] = -sine;
    transform.matrix[2][2] = cosine;

    return transform;
}

Transform Transform::zRotation(double angle) {
    Transform transform;

    double cosine = cos(angle);
    double sine = sin(angle);

    transform.matrix[0][0] = cosine;
    transform.matrix[0][1] = -sine;
    transform.matrix[1][0] = sine;
    transform.matrix[1][1] = cosine;

    return transform;
}

Transform Transform::shearing(double xToY, double xToZ, double yToX, double yToZ, double zToX, double zToY) {
    Transform transform;

    transform.matrix[0][1] = xToY;
    transform.matrix[0][2] = xToZ;
    transform.matrix[1][0] = yToX;
    transform.matrix[1][2] = yToZ;
    transform.matrix[2][0] = zToX;
    transform.matrix[2][1] = zToY;

    return transform;
}

//TODO: Change function call to * operator
//TODO: To have normal order change this->multiply(other) to other.multiply(this)
Transform &Transform::translate(double x, double y, double z) {
    return this->multiplyTransforms(Transform::translation(x, y, z));
}

Transform &Transform::scale(double x, double y, double z) {
    return this->multiplyTransforms(Transform::scaling(x, y, z));
}

Transform &Transform::rotateX(double angle) {
    return this->multiplyTransforms(Transform::xRotation(angle));
}

Transform &Transform::rotateY(double angle) {
    return this->multiplyTransforms(Transform::yRotation(angle));
}

Transform &Transform::rotateZ(double angle) {
    return this->multiplyTransforms(Transform::zRotation(angle));
}

Transform &Transform::shear(double xToY, double xToZ, double yToX, double yToZ, double zToX, double zToY) {
    return this->multiplyTransforms(Transform::shearing(xToY, xToZ, yToX, yToZ, zToX, zToY));
}

//TODO: Refactor so operation can work both on Matrix and Transform
//TODO: Fix this shit (not efficient)
Transform &Transform::multiplyTransforms(const Transform &other) {
    //Bugged because it changed the matrix while calculating it 🤦
    Transform temp;
    for (int i = 0; i < this->sizeY; ++i) {
        for (int j = 0; j < this->sizeX; ++j) {
            temp[i][j] = this->matrix[i][0] * other[0][j] + this->matrix[i][1] * other[1][j] +
                         this->matrix[i][2] * other[2][j] + this->matrix[i][3] * other[3][j];
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->matrix[i][j] = temp[i][j];
        }
    }

    return *this;
}
