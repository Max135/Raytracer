//
// Created by Max on 2021-01-01.
//

#ifndef RAYTRACER_TUPLE_H
#define RAYTRACER_TUPLE_H


#include <string>
#include "../Helper.h"

class Tuple {
public:
    double x, y, z, w;

    Tuple() {}

    Tuple(double x, double y, double z, double w);

    static Tuple point(double x, double y, double z);

    static Tuple vector(double x, double y, double z);

    double magnitude() const;

    double quickInverseSquareRoot(double number);

    Tuple fastNormalize();

    Tuple normalize() const;

    Tuple cross(const Tuple& other) const;

    double dot(const Tuple& other) const;

    Tuple reflectOff(const Tuple& other);

    std::string toString() const;

    Tuple operator+(const Tuple &other) const;

    Tuple operator-(const Tuple &other) const;

    Tuple operator*(const double &scalar) const;

    Tuple operator*(const Tuple &other) const;

    Tuple operator/(const double &scalar) const;

    Tuple operator+=(const Tuple &other) const;

    virtual Tuple &operator=(const Tuple &other);

    bool operator==(const Tuple &other) const;

    bool operator!=(const Tuple &other) const;

    Tuple operator-() const;


private:
    static bool areEqual(const Tuple& first, const Tuple& second);

    static Tuple add(const Tuple& first, const Tuple& second);

    static Tuple subtract(const Tuple& first, const Tuple& second);

    static Tuple negate(const Tuple& tuple);

    static Tuple multiplyScalar(const Tuple& tuple, double scalar);

    static Tuple multiply(const Tuple& first, const Tuple& second);

    static Tuple divideScalar(const Tuple& tuple, double scalar);
};

#endif //RAYTRACER_TUPLE_H
