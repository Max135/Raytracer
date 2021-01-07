//
// Created by Max on 2021-01-05.
//

#include "Transform.h"

Transform Transform::translation(float x, float y, float z) {
    Transform transform;

    transform.matrix[0][3] = x;
    transform.matrix[1][3] = y;
    transform.matrix[2][3] = z;

    return transform;
}

Transform Transform::scaling(float x, float y, float z) {
    Transform transform;

    transform.matrix[0][0] = x;
    transform.matrix[1][1] = y;
    transform.matrix[2][2] = z;

    return transform;
}

Transform Transform::xRotation(float angle) {
    Transform transform;

    float cosine = cos(angle);
    float sine = sin(angle);

    transform.matrix[1][1] = cosine;
    transform.matrix[1][2] = -sine;
    transform.matrix[2][1] = sine;
    transform.matrix[2][2] = cosine;

    return transform;
}

Transform Transform::yRotation(float angle) {
    Transform transform;

    float cosine = cos(angle);
    float sine = sin(angle);

    transform.matrix[0][0] = cosine;
    transform.matrix[0][2] = sine;
    transform.matrix[2][0] = -sine;
    transform.matrix[2][2] = cosine;

    return transform;
}

Transform Transform::zRotation(float angle) {
    Transform transform;

    float cosine = cos(angle);
    float sine = sin(angle);

    transform.matrix[0][0] = cosine;
    transform.matrix[0][1] = -sine;
    transform.matrix[1][0] = sine;
    transform.matrix[1][1] = cosine;

    return transform;
}

void Transform::translate(float x, float y, float z) {

}

void Transform::scale(float x, float y, float z) {

}
