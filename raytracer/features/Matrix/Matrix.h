//
// Created by Max on 2021-01-03.
//

#ifndef RAYTRACER_MATRIX_H
#define RAYTRACER_MATRIX_H


#include "../Tuple/Tuples.h"

class Matrix {
public:
    int sizeX, sizeY;

    Matrix(int x, int y) {
        this->sizeX = x;
        this->sizeY = y;

        matrix = initializeMatrix();
    }

    ~Matrix() {
        for (int i = 0; i < sizeY; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }

    static Matrix identityMatrix(int size = 4);

    float* operator [] (int pos) {
        return matrix[pos];
    }

    float* operator [] (int pos) const {
        return matrix[pos];
    }

    Matrix operator * (const Matrix &other) {
        return multiplyMatrices(other);
    }

    Tuple operator * (const Tuple &tuple) {
        return multiplyTuple(tuple);
    }

    bool operator == (const Matrix &other) {
        return compareMatrix(other);
    }

private:
    float** matrix;
    float** initializeMatrix();
    bool compareMatrix(const Matrix &other);
    Matrix multiplyMatrices(const Matrix &other);
    Tuple multiplyTuple(const Tuple &tuple);
};


#endif //RAYTRACER_MATRIX_H
