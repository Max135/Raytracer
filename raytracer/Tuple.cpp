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

Tuple Tuple::multiplyScalar(Tuple a, float scalar) {
    Tuple tuple;

    tuple.x = a.x * scalar;
    tuple.y = a.y * scalar;
    tuple.z = a.z * scalar;
    tuple.w = a.w * scalar;

    return tuple;
}

Tuple Tuple::divideScalar(Tuple a, float scalar) {
    Tuple tuple;

    tuple.x = a.x / scalar;
    tuple.y = a.y / scalar;
    tuple.z = a.z / scalar;
    tuple.w = a.w / scalar;

    return tuple;
}

float Tuple::magnitude() {
    return (float) sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) + pow(this->w, 2));
}

//3x faster then real calculation with ~1% approximation
float Tuple::quickInverseSquareRoot(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;


    i = * (long * ) &y;                   //Gets the binary representation of the float in long to get access to bit shit operator
                                          //Get the address of y (&y) then change its internal representation to a long ((long * ))
                                          //then read what it is (*) as if it were a long

    i = 0x5f3759df - (i >> 1);            //Changes the exponent part inside float representation (IEEE 754),
                                          //so instead of calculating sqrt, we divide exponent by 2 (i >> 1) (bit shifting to right == /2)
                                          //Hard coded number exploit the fact that the log of float is its own binary representation

    y = * (float * ) &i;                  //Revert the number to a float with same principle as before

//    Newton iteration
    y = y * (threehalfs - (x2 * y * y));  //Better approximate the root of the number using the function and its derivative

    return y;
}

Tuple Tuple::normalize() {
    Tuple normalized;

    float inverseSquare = quickInverseSquareRoot(this->x * this->x + this->y * this->y + this->z * this->z);

    normalized.x = this->x * inverseSquare;
    normalized.y = this->y * inverseSquare;
    normalized.z = this->z * inverseSquare;
    normalized.w = this->w;

    return normalized;
}

Tuple Tuple::preciseNormalize() {
    Tuple normalized;

    float magnitude = this->magnitude();

    normalized.x = this->x / magnitude;
    normalized.y = this->y / magnitude;
    normalized.z = this->z / magnitude;
    normalized.w = this->w / magnitude;

    return normalized;
}
