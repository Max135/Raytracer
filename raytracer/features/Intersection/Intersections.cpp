//
// Created by Max on 2021-02-06.
//

#include "Intersections.h"

void Intersections::append(std::vector<Intersection> intersections) {
    this->xs.insert(this->xs.end(), intersections.begin(), intersections.end());
}

void Intersections::append(Intersections intersections) {
    this->append(intersections.xs);
}

void Intersections::sort() {
    Intersections::quickSortIntersections(&this->xs, 0, this->xs.size());
}

Intersection Intersections::hit() {
    for (Intersection i : this->xs) {
        if (i.t >= 0) return i;
    }

    return {};
}

//TODO: if vectors are often nearly sorted switch to insertion sort which is fastest in this situation
void Intersections::quickSortIntersections(std::vector<Intersection> *vector, int startIndex, int endIndex) {
    if (endIndex <= startIndex) return;
    int lastSorted = partition(vector, startIndex, endIndex);
    quickSortIntersections(vector, startIndex, lastSorted - 1);
    quickSortIntersections(vector, lastSorted + 1, endIndex);
}

//TODO: Test speed with and without temp vector
int Intersections::partition(std::vector<Intersection> *vector, int startIndex, int endIndex) {
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

int Intersections::size() const {
    return this->xs.size();
}
