//
// Created by Max on 2021-01-03.
//

#ifndef RAYTRACER_MATRIX_H
#define RAYTRACER_MATRIX_H


#include <iostream>
#include <algorithm>
#include "../Helper.h"
#include "../Tuple/Tuples.h"

class Matrix {
public:
    int sizeX, sizeY;

    Matrix(int sizeX, int sizeY);

    //Copy constructor, https://www.geeksforgeeks.org/copy-constructor-in-cpp/
    Matrix(const Matrix &m2);

    ~Matrix();

    static Matrix identityMatrix(int size = 4);

    Matrix transpose();

    Matrix submatrix(int row, int column);

    Matrix inverse();

    double minor(int row, int column);

    double cofactor(int row, int column);

    double determinant();

    bool isInvertible();

    std::string toString();

    double *operator[](int pos);

    double *operator[](int pos) const;

    Matrix operator*(const Matrix &other);

    Tuple operator*(const Tuple &tuple);

    bool operator==(const Matrix &other);

    Matrix &operator=(const Matrix &other);

protected:
    double **matrix;

    void setToIdentityMatrix();

private:
    double **initializeMatrix() const;

    double **initializeMatrix(const Matrix &other) const;

    bool compareMatrix(const Matrix &other);

    Matrix multiplyMatrices(const Matrix &other);

    Tuple multiplyTuple(const Tuple &tuple);
};


#endif //RAYTRACER_MATRIX_H
