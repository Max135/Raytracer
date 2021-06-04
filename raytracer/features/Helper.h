//
// Created by Max on 2021-01-01.
//

#ifndef RAYTRACER_HELPER_H
#define RAYTRACER_HELPER_H

#define EPSILON 0.00001

class Helper {
//    constexpr static const double EPSILON = 0.00001;

public:
    static bool compareFloat(double a, double b);

    static bool compareFloat(double a, double b, double range);

    static double getEPSILON();
};


#endif //RAYTRACER_HELPER_H
