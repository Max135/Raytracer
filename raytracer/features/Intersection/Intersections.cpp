//
// Created by Max on 2021-02-06.
//

#include "Intersections.h"

Intersections::Intersections(std::vector<Intersection> intersections) {
    this->xs = std::move(intersections);
}

Intersections::Intersections(const Intersections &intersections) {
    this->xs = intersections.xs;
}

Intersection Intersections::operator[](int pos) {
    return this->xs[pos];
}

Intersection Intersections::operator[](int pos) const {
    return this->xs[pos];
}

void Intersections::append(const std::vector<Intersection> &intersections) {
    this->xs.insert(this->xs.end(), intersections.begin(), intersections.end());
}

void Intersections::append(const Intersections &intersections) {
    this->append(intersections.xs);
}

void Intersections::sort() {
    Intersections::quickSortIntersections(&this->xs, 0, this->xs.size() - 1); //😤 forgot -1
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

int Intersections::partition(std::vector<Intersection> *vector, int startIndex, int endIndex) {
    int i = startIndex - 1, j = endIndex;
    Intersection value = vector->at(endIndex);
    for (;;) {
        while (vector->at(++i).t < value.t);
        while (value.t < vector->at(--j).t) {
            if (j == startIndex) break;
        }
        if (i >= j) break;
        std::swap(vector->at(i), vector->at(j));
    }
    std::swap(vector->at(i), vector->at(endIndex));
    return i;
}

int Intersections::size() const {
    return this->xs.size();
}

bool Intersections::empty() const {
    return this->xs.empty();
}

std::string Intersections::toString() {
    std::string string;
    string.append("[ ");
    for (auto &object: this->xs) {
        string.append(object.toString());
        string.append(", ");
    }
    string.append("]\n");
    return string;
}
