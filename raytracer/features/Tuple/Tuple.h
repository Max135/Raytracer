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

    double magnitude();

    double quickInverseSquareRoot(double number);

    Tuple fastNormalize();

    Tuple normalize();

    Tuple cross(Tuple other);

    double dot(Tuple other);

    Tuple reflectOff(Tuple other);

    std::string toString() const;

    Tuple operator+(const Tuple &other);

    Tuple operator-(const Tuple &other);

    Tuple operator*(const double &scalar);

    Tuple operator*(const Tuple &other);

    Tuple operator/(const double &scalar);

    Tuple operator+=(const Tuple &other);

    virtual Tuple &operator=(const Tuple &other);

    bool operator==(const Tuple &other);

    bool operator!=(const Tuple &other);

    Tuple operator-();


private:
    static bool areEqual(Tuple first, Tuple second);

    static Tuple add(Tuple first, Tuple second);

    static Tuple subtract(Tuple first, Tuple second);

    static Tuple negate(Tuple tuple);

    static Tuple multiplyScalar(Tuple tuple, double scalar);

    static Tuple multiply(Tuple first, Tuple second);

    static Tuple divideScalar(Tuple tuple, double scalar);
};

#endif //RAYTRACER_TUPLE_H
