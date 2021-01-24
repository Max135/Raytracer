//
// Created by Max on 2021-01-20.
//

#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H

#include <vector>
#include "../Shape/Sphere.h"

///https://stackoverflow.com/questions/1657883/variable-number-of-arguments-in-c/49435122
///https://www.stroustrup.com/C++11FAQ.html#variadic-templates
///https://kevinushey.github.io/blog/2016/01/27/introduction-to-c++-variadic-templates/

///https://www.geeksforgeeks.org/templates-cpp/

class Intersection {
public:
    float t;
    Sphere *sphere;

    Intersection(float t, Sphere *sphere) : t(t), sphere(sphere) {}

    Intersection() {t = 0; sphere = nullptr;}

    bool operator == (const Intersection &other);


    static Intersection hit(std::vector<Intersection> vector);

    template<typename T>
    static std::vector<Intersection> intersections(T t) {
        std::vector<Intersection> vector;
        vector.push_back(t);
        return vector;
    }

    template<typename T, typename... Ts>
    static std::vector<Intersection> intersections(T t, Ts... intersections) {
        //Add all elements to array
        std::vector<Intersection> vector;
        recursiveIntersections<std::vector<Intersection> *, T, Ts...>(&vector, t, intersections...);

        //Sort array
        quickSortIntersections(&vector, 0, vector.size()-1);

        return vector;
    }

private:
    static void quickSortIntersections(std::vector<Intersection> *vector, int startIndex, int endIndex);

    static int partition(std::vector<Intersection> array[], int startIndex, int endIndex);

    template<typename Vec, typename T, typename... Ts>
    static void recursiveIntersections(Vec vector, T t, Ts... ts) {
        std::vector<Intersection> *temp = vector;
        temp->push_back(t);
        recursiveIntersections<std::vector<Intersection> *, Ts...>(vector, ts...);
    }

    template<typename Vec, typename T>
    static void recursiveIntersections(Vec vector, T t) {
        std::vector<Intersection> *temp = vector;
        temp->push_back(t);
    }
};


#endif //RAYTRACER_INTERSECTION_H
