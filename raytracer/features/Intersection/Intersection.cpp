//
// Created by Max on 2021-01-20.
//

#include "Intersection.h"

void Intersection::quickSortIntersections(std::vector<Intersection> *vector, int startIndex, int endIndex) {
    if (endIndex <= startIndex) return;
    int lastSorted = partition(vector, startIndex, endIndex);
    quickSortIntersections(vector, startIndex, lastSorted-1);
    quickSortIntersections(vector, lastSorted+1, endIndex);
}

//TODO: Test speed with and without temp vector
int Intersection::partition(std::vector<Intersection> *vector, int startIndex, int endIndex) {
    std::vector<Intersection> &array = *vector;

    int i = startIndex - 1, j = endIndex;
    Intersection value = array[endIndex];
    for (;;) {
        while (array[++i].t < value.t);
        while (value.t < array[--j].t)
        {
            if (j == startIndex) break;
        }
        if (i >= j) break;
        std::swap(array[i], array[j]);
    }
    std::swap(array[i], array[endIndex]);
    return i;
}
