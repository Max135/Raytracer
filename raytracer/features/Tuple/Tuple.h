//
// Created by Max on 2021-01-01.
//

#ifndef RAYTRACER_TUPLE_H
#define RAYTRACER_TUPLE_H


#include <string>

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

    float magnitude();

    float quickInverseSquareRoot(float number);

    Tuple normalize();

    Tuple preciseNormalize();

    Tuple cross(Tuple other);

    float dot(Tuple other);

    std::string toString() const;

    Tuple operator+(const Tuple &other) {
        return add(*this, other);
    }

    Tuple operator-(const Tuple &other) {
        return subtract(*this, other);
    }

    Tuple operator*(const float &scalar) {
        return multiplyScalar(*this, scalar);
    }

    Tuple operator*(const Tuple &other) {
        return multiply(*this, other);
    }

    Tuple operator/(const float &scalar) {
        return divideScalar(*this, scalar);
    }

    bool operator==(const Tuple &other) {
        return areEqual(*this, other);
    }

    bool operator!=(const Tuple &other) {
        return !areEqual(*this, other);
    }

    Tuple operator-() {
        return negate(*this);
    }


private:
    static bool areEqual(Tuple first, Tuple second);

    static Tuple add(Tuple first, Tuple second);

    static Tuple subtract(Tuple first, Tuple second);

    static Tuple negate(Tuple tuple);

    static Tuple multiplyScalar(Tuple tuple, float scalar);

    static Tuple multiply(Tuple first, Tuple second);

    static Tuple divideScalar(Tuple tuple, float scalar);
};

#endif //RAYTRACER_TUPLE_H
