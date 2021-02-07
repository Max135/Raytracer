//
// Created by Max on 2021-02-06.
//

#ifndef RAYTRACER_INTERSECTIONS_H
#define RAYTRACER_INTERSECTIONS_H


#include <utility>
#include <vector>
#include "Junctions.h"


///https://stackoverflow.com/questions/1657883/variable-number-of-arguments-in-c/49435122
///https://www.stroustrup.com/C++11FAQ.html#variadic-templates
///https://kevinushey.github.io/blog/2016/01/27/introduction-to-c++-variadic-templates/

///https://www.geeksforgeeks.org/templates-cpp/

class Intersections {
public:
    std::vector<Intersection> xs;

    Intersections() {}

    Intersections(std::vector<Intersection> intersections) {
        this->xs = std::move(intersections);
    }

    Intersections(Intersections const &intersections) {
        this->xs = std::move(intersections.xs);
    }

    Intersection operator[](int pos) {
        return this->xs[pos];
    }

    Intersection operator[](int pos) const {
        return this->xs[pos];
    }

    void append(const std::vector<Intersection>& intersections);

    void append(const Intersections& intersections);

    void sort();

    int size() const;

    bool empty() const;

    std::string toString();

    Intersection hit();

    template<typename T>
    static Intersections intersections(T t) {
        Intersections intersections;
        intersections.xs.push_back(t);
        return intersections;
    }

    template<typename T, typename... Ts>
    static Intersections intersections(T t, Ts... intersections) {
        //Add all elements to array
        Intersections intersectionsClass;
        recursiveIntersections<std::vector<Intersection> *, T, Ts...>(&intersectionsClass.xs, t, intersections...);

        //Sort array
        quickSortIntersections(&intersectionsClass.xs, 0, intersectionsClass.xs.size() - 1);

        return intersectionsClass;
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


#endif //RAYTRACER_INTERSECTIONS_H
