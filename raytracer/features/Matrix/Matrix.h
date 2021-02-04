//
// Created by Max on 2021-01-03.
//

#ifndef RAYTRACER_MATRIX_H
#define RAYTRACER_MATRIX_H

#include <iostream>
#include "../Tuple/Tuples.h"

class Matrix {
public:
    int sizeX, sizeY;

    Matrix(int sizeX, int sizeY) {
        this->sizeX = sizeX;
        this->sizeY = sizeY;

        matrix = initializeMatrix();
    }

    //Copy constructor, https://www.geeksforgeeks.org/copy-constructor-in-cpp/
    Matrix(const Matrix &m2) {
        this->sizeX = m2.sizeX;
        this->sizeY = m2.sizeY;

        this->matrix = initializeMatrix(m2);
    }

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

    Matrix &operator=(const Matrix &other) {
        if (this == &other)
            return *this;

        this->sizeX = other.sizeX;
        this->sizeY = other.sizeY;

        for (int i = 0; i < this->sizeY; ++i) {
            for (int j = 0; j < this->sizeX; ++j) {
                this->matrix[i][j] = other.matrix[i][j];
            }
        }

        return *this;
    }

protected:
    float **matrix;

    void setToIdentityMatrix();

private:
    float **initializeMatrix() const;

    float **initializeMatrix(const Matrix &other) const;

    bool compareMatrix(const Matrix &other);

    Matrix multiplyMatrices(const Matrix &other);

    Tuple multiplyTuple(const Tuple &tuple);
};


#endif //RAYTRACER_MATRIX_H
