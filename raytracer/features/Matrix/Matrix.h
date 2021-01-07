//
// Created by Max on 2021-01-03.
//

#ifndef RAYTRACER_MATRIX_H
#define RAYTRACER_MATRIX_H


#include "../Tuple/Tuples.h"

class Matrix {
public:
    int sizeX, sizeY;

    Matrix(int sizeX, int sizeY) {
        this->sizeX = sizeX;
        this->sizeY = sizeY;

        matrix = initializeMatrix();
    }

    //TODO: Copy constructor, https://www.geeksforgeeks.org/copy-constructor-in-cpp/

    ~Matrix() {
        for (int i = 0; i < sizeY; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }

    static Matrix identityMatrix(int size = 4);

    Matrix transpose();

    Matrix submatrix(int row, int column);

    Matrix inverse();

    float minor(int row, int column);

    float cofactor(int row, int column);

    float determinant();

    bool isInvertible();

    std::string toString();

    float *operator[](int pos) {
        return matrix[pos];
    }

    float *operator[](int pos) const {
        return matrix[pos];
    }

    Matrix operator*(const Matrix &other) {
        return multiplyMatrices(other);
    }

    Tuple operator*(const Tuple &tuple) {
        return multiplyTuple(tuple);
    }

    bool operator==(const Matrix &other) {
        return compareMatrix(other);
    }

protected:
    float **matrix;

    void setToIdentityMatrix();

private:
    float **initializeMatrix();

    bool compareMatrix(const Matrix &other);

    Matrix multiplyMatrices(const Matrix &other);

    Tuple multiplyTuple(const Tuple &tuple);
};


#endif //RAYTRACER_MATRIX_H
