//
// Created by Max on 2021-01-03.
//

#include <algorithm>
#include "../Helper.h"
#include "Matrix.h"

float **Matrix::initializeMatrix() {
    float **grid = new float *[this->sizeY];
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

//TODO: Adapt for any sized matrix
Matrix Matrix::multiplyMatrices(const Matrix &other) {
    Matrix result(4, 4);

    for (int i = 0; i < this->sizeY; ++i) {
        for (int j = 0; j < this->sizeX; ++j) {
            result[i][j] = this->matrix[i][0] * other[0][j] + this->matrix[i][1] * other[1][j] +
                           this->matrix[i][2] * other[2][j] + this->matrix[i][3] * other[3][j];
        }
    }
    return result;
}

Tuple Matrix::multiplyTuple(const Tuple &tuple) {
    float temp[4];

    for (int i = 0; i < sizeY; ++i) {
        temp[i] = this->matrix[i][0] * tuple.x + this->matrix[i][1] * tuple.y + this->matrix[i][2] * tuple.z +
                  this->matrix[i][3] * tuple.w;
    }

    return Tuple(temp[0], temp[1], temp[2], temp[3]);
}

Matrix Matrix::identityMatrix(int size) {
    Matrix matrix(size, size);
    for (int i = 0; i < size; ++i) {
        matrix[i][i] = 1;
    }

    return matrix;
}

Matrix Matrix::transpose() {
    Matrix result(this->sizeY, this->sizeX);

    for (int i = 0; i < this->sizeY; ++i) {
        for (int j = 0; j < this->sizeX; ++j) {
            result[j][i] = this->matrix[i][j];
        }
    }

    return result;
}

float Matrix::determinant() {
    return this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] * this->matrix[1][0];
}

Matrix Matrix::submatrix(int row, int column) {
    Matrix result(this->sizeX - 1, this->sizeY - 1);

    int yPos = 0;

    for (int i = 0; i < this->sizeY; ++i) {
        if (i != row) {
            int xPos = 0;
            for (int j = 0; j < this->sizeX; ++j) {
                if (j != column) {
                    result[yPos][xPos] = this->matrix[i][j];
                    xPos++;
                }
            }
            yPos++;
        }
    }

    return result;
}

