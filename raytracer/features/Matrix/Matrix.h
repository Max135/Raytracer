//
// Created by Max on 2021-01-03.
//

#ifndef RAYTRACER_MATRIX_H
#define RAYTRACER_MATRIX_H


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

    float* operator [] (int pos) {
        return matrix[pos];
    }

    bool operator == (const Matrix &other) {
        return compareMatrix(other);
    }

private:
    float** matrix;
    float** initializeMatrix();
    bool compareMatrix(const Matrix &other);
};


#endif //RAYTRACER_MATRIX_H
