//
// Created by Max on 2021-01-01.
//

#include "Tuple.h"

Tuple::Tuple(double x, double y, double z, double w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Tuple Tuple::point(double x, double y, double z) {
    return Tuple(x, y, z, 1.0);
}

Tuple Tuple::vector(double x, double y, double z) {
    return Tuple(x, y, z, 0.0);
}

Tuple Tuple::operator+(const Tuple &other) const {
    return add(*this, other);
}

Tuple Tuple::operator-(const Tuple &other) const {
    return subtract(*this, other);
}

Tuple Tuple::operator*(const double &scalar) const {
    return multiplyScalar(*this, scalar);
}

Tuple Tuple::operator*(const Tuple &other) const {
    return multiply(*this, other);
}

Tuple Tuple::operator/(const double &scalar) const {
    return divideScalar(*this, scalar);
}

Tuple Tuple::operator+=(const Tuple &other) const {
    return *this + other;
}

Tuple &Tuple::operator=(const Tuple &other) {
    if (this == &other)
        return *this;

    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;

    return *this;
}

bool Tuple::operator==(const Tuple &other) const {
    return areEqual(*this, other);
}

bool Tuple::operator!=(const Tuple &other) const {
    return !areEqual(*this, other);
}

Tuple Tuple::operator-() const {
    return negate(*this);
}


bool Tuple::areEqual(const Tuple& first, const Tuple& second) {
    return Helper::compareFloat(first.x, second.x)
           && Helper::compareFloat(first.y, second.y)
           && Helper::compareFloat(first.z, second.z)
           && Helper::compareFloat(first.w, second.w);
}

Tuple Tuple::add(const Tuple& first, const Tuple& second) {
    Tuple tuple;

    tuple.x = first.x + second.x;
    tuple.y = first.y + second.y;
    tuple.z = first.z + second.z;
    tuple.w = first.w + second.w;

    return tuple;
}

Tuple Tuple::subtract(const Tuple& first, const Tuple& second) {
    Tuple tuple;

    tuple.x = first.x - second.x;
    tuple.y = first.y - second.y;
    tuple.z = first.z - second.z;
    tuple.w = first.w - second.w;

    return tuple;
}

Tuple Tuple::negate(const Tuple& tuple) {
    Tuple tempTuple;

    tempTuple.x = -tuple.x;
    tempTuple.y = -tuple.y;
    tempTuple.z = -tuple.z;
    tempTuple.w = -tuple.w;

    return tempTuple;
}

Tuple Tuple::multiply(const Tuple& first, const Tuple& second) {
    Tuple tuple;

    tuple.x = first.x * second.x;
    tuple.y = first.y * second.y;
    tuple.z = first.z * second.z;
    tuple.w = first.w * second.w;

    return tuple;
}

Tuple Tuple::multiplyScalar(const Tuple& tuple, double scalar) {
    Tuple tempTuple;

    tempTuple.x = tuple.x * scalar;
    tempTuple.y = tuple.y * scalar;
    tempTuple.z = tuple.z * scalar;
    tempTuple.w = tuple.w * scalar;

    return tempTuple;
}

Tuple Tuple::divideScalar(const Tuple& tuple, double scalar) {
    Tuple tempTuple;

    tempTuple.x = tuple.x / scalar;
    tempTuple.y = tuple.y / scalar;
    tempTuple.z = tuple.z / scalar;
    tempTuple.w = tuple.w / scalar;

    return tempTuple;
}

double Tuple::magnitude() const {
    return (double) sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) + pow(this->w, 2));
}

//3x faster then real calculation with ~1% approximation
double Tuple::quickInverseSquareRoot(double number) {
    long i;
    double x2, y;
    const double threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;

    //Gets the binary representation of the double in long to get access to bit shit operator get the address of y (&y) then change its internal representation to a long ((long * )) then read what it is (*) as if it were a long
    i = *(long *) &y;

    //Changes the exponent part inside double representation (IEEE 754), so instead of calculating sqrt, we divide exponent by 2 (i >> 1) (bit shifting to right == /2) hard coded number exploit the fact that the log of double is its own binary representation
    i = 0x5f3759df - (i >> 1);

    //Revert the number to a double with same principle as before
    y = *(double *) &i;

    //Use Newton iteration to better approximate the root of the number using the function and its derivative
    y = y * (threehalfs - (x2 * y * y));

    return y;
}

Tuple Tuple::fastNormalize() {
    Tuple normalized;

    double inverseSquare = quickInverseSquareRoot(this->x * this->x + this->y * this->y + this->z * this->z);

    normalized.x = this->x * inverseSquare;
    normalized.y = this->y * inverseSquare;
    normalized.z = this->z * inverseSquare;
    normalized.w = this->w;

    return normalized;
}

Tuple Tuple::normalize() const {
    Tuple normalized;

    double magnitude = this->magnitude();

    normalized.x = this->x / magnitude;
    normalized.y = this->y / magnitude;
    normalized.z = this->z / magnitude;
    normalized.w = this->w / magnitude;

    return normalized;
}

Tuple Tuple::cross(const Tuple& other) const {
    return Tuple::vector(this->y * other.z - this->z * other.y,
                         this->z * other.x - this->x * other.z,
                         this->x * other.y - this->y * other.x);
}

double Tuple::dot(const Tuple& other) const {
    return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
}

std::string Tuple::toString() const {
    std::string string;
    string.append("x: ");
    string.append(std::to_string(x));
    string.append(" y: ");
    string.append(std::to_string(y));
    string.append(" z: ");
    string.append(std::to_string(z));
    return string;
}

Tuple Tuple::reflectOff(const Tuple& other) {
    return *this - other * 2 * this->dot(other);
}
