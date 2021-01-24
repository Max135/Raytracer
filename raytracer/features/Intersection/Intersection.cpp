//
// Created by Max on 2021-01-20.
//

#include "Intersection.h"

//TODO: if vectors are often nearly sorted switch to insertion sort which is fastest in this situation
void Intersection::quickSortIntersections(std::vector<Intersection> *vector, int startIndex, int endIndex) {
    if (endIndex <= startIndex) return;
    int lastSorted = partition(vector, startIndex, endIndex);
    quickSortIntersections(vector, startIndex, lastSorted - 1);
    quickSortIntersections(vector, lastSorted + 1, endIndex);
}

//TODO: Test speed with and without temp vector
int Intersection::partition(std::vector<Intersection> *vector, int startIndex, int endIndex) {
    std::vector<Intersection> &array = *vector;

    int i = startIndex - 1, j = endIndex;
    Intersection value = array[endIndex];
    for (;;) {
        while (array[++i].t < value.t);
        while (value.t < array[--j].t) {
            if (j == startIndex) break;
        }
        if (i >= j) break;
        std::swap(array[i], array[j]);
    }
    std::swap(array[i], array[endIndex]);
    return i;
}

bool Intersection::operator==(const Intersection &other) {
    return (this->t == other.t && this->sphere == other.sphere);
}

Intersection Intersection::hit(std::vector<Intersection> vector) {
    for (Intersection &i : vector) {
        if (i.t >= 0) return i;
    }

    return {};
}
