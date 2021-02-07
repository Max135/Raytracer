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

    Tuple(float x, float y, float z, float w);

    static Tuple point(float x, float y, float z);

    static Tuple vector(float x, float y, float z);

    float magnitude();

    float quickInverseSquareRoot(float number);

    Tuple fastNormalize();

    Tuple normalize();

    Tuple cross(Tuple other);

    float dot(Tuple other);

    Tuple reflectOff(Tuple other);

    std::string toString() const;

    Tuple operator+(const Tuple &other);

    Tuple operator-(const Tuple &other);

    Tuple operator*(const float &scalar);

    Tuple operator*(const Tuple &other);

    Tuple operator/(const float &scalar);

    virtual Tuple &operator=(const Tuple &other);

    bool operator==(const Tuple &other);

    bool operator!=(const Tuple &other);

    Tuple operator-();


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
