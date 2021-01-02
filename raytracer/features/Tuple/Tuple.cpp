//
// Created by Max on 2021-01-01.
//

#include <string>
#include "Tuple.h"
#include "../Helper.h"

bool Tuple::areEqual(Tuple first, Tuple second) {
    return Helper::compareFloat(first.x, second.x)
    && Helper::compareFloat(first.y, second.y)
    && Helper::compareFloat(first.z, second.z)
    && Helper::compareFloat(first.w, second.w);
}

Tuple Tuple::add(Tuple first, Tuple second) {
    Tuple tuple;

    tuple.x = first.x + second.x;
    tuple.y = first.y + second.y;
    tuple.z = first.z + second.z;
    tuple.w = first.w + second.w;

    return tuple;
}

Tuple Tuple::subtract(Tuple first, Tuple second) {
    Tuple tuple;

    tuple.x = first.x - second.x;
    tuple.y = first.y - second.y;
    tuple.z = first.z - second.z;
    tuple.w = first.w - second.w;

    return tuple;
}

Tuple Tuple::negate(Tuple tuple) {
    Tuple tempTuple;

    tempTuple.x = -tuple.x;
    tempTuple.y = -tuple.y;
    tempTuple.z = -tuple.z;
    tempTuple.w = -tuple.w;

    return tempTuple;
}

float Tuple::multiply(Tuple first, Tuple second) {
    return first.x * second.x + first.y * second.y + first.z * second.z + first.w * second.w;
}

Tuple Tuple::multiplyScalar(Tuple tuple, float scalar) {
    Tuple tempTuple;

    tempTuple.x = tuple.x * scalar;
    tempTuple.y = tuple.y * scalar;
    tempTuple.z = tuple.z * scalar;
    tempTuple.w = tuple.w * scalar;

    return tempTuple;
}

Tuple Tuple::divideScalar(Tuple tuple, float scalar) {
    Tuple tempTuple;

    tempTuple.x = tuple.x / scalar;
    tempTuple.y = tuple.y / scalar;
    tempTuple.z = tuple.z / scalar;
    tempTuple.w = tuple.w / scalar;

    return tempTuple;
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

    i = * (long * ) &y;                   //Gets the binary representation of the float in long to get access to bit shit operator get the address of y (&y) then change its internal representation to a long ((long * )) then read what it is (*) as if it were a long
    i = 0x5f3759df - (i >> 1);            //Changes the exponent part inside float representation (IEEE 754), so instead of calculating sqrt, we divide exponent by 2 (i >> 1) (bit shifting to right == /2) hard coded number exploit the fact that the log of float is its own binary representation
    y = * (float * ) &i;                  //Revert the number to a float with same principle as before

    y = y * (threehalfs - (x2 * y * y));  //Use Newton iteration to better approximate the root of the number using the function and its derivative

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

Tuple Tuple::cross(Tuple other) {
    return Tuple::vector(this->y * other.z - this->z * other.y,
                         this->z * other.x - this->x * other.z,
                         this->x * other.y - this->y * other.x);
}
