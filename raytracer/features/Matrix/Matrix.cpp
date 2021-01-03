//
// Created by Max on 2021-01-03.
//

#include "../Helper.h"
#include "Matrix.h"

float** Matrix::initializeMatrix() {
    float** grid = new float* [this->sizeY];
    for (int i = 0; i < this->sizeY; ++i) {
        grid[i] = new float[this->sizeX];
        for (int j = 0; j < this->sizeX; ++j) {
            grid[i][j] = 0.0;
        }
    }
    return grid;
}

bool Matrix::compareMatrix(const Matrix &other) {
    if (this->sizeX != other.sizeX || this->sizeY != other.sizeY) return false;

    for (int i = 0; i < this->sizeY; ++i) {
        for (int j = 0; j < this->sizeX; ++j) {
            if (!Helper::compareFloat(this->matrix[i][j], other.matrix[i][j])) {
                return false;
            }
        }
    }
    return true;
}
