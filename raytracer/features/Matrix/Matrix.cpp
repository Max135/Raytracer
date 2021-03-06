//
// Created by Max on 2021-01-03.
//

#include "Matrix.h"

Matrix::Matrix(int sizeX, int sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;

    matrix = initializeMatrix();
}

Matrix::Matrix(const Matrix &m2) {
    this->sizeX = m2.sizeX;
    this->sizeY = m2.sizeY;

    this->matrix = initializeMatrix(m2);
}

Matrix::~Matrix() {
    for (int i = 0; i < sizeY; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}

double *Matrix::operator[](int pos) {
    return matrix[pos];
}

double *Matrix::operator[](int pos) const {
    return matrix[pos];
}

Matrix Matrix::operator*(const Matrix &other) {
    return multiplyMatrices(other);
}

Tuple Matrix::operator*(const Tuple &tuple) {
    return multiplyTuple(tuple);
}

bool Matrix::operator==(const Matrix &other) {
    return compareMatrix(other);
}

Matrix &Matrix::operator=(const Matrix &other) {
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

double **Matrix::initializeMatrix() const {
    double **grid = new double *[this->sizeY];
    for (int i = 0; i < this->sizeY; ++i) {
        grid[i] = new double[this->sizeX];
        for (int j = 0; j < this->sizeX; ++j) {
            grid[i][j] = 0.0;
        }
    }
    return grid;
}

double **Matrix::initializeMatrix(const Matrix &other) const {
    double **grid = new double *[this->sizeY];
    for (int i = 0; i < this->sizeY; ++i) {
        grid[i] = new double[this->sizeX];
        for (int j = 0; j < this->sizeX; ++j) {
            grid[i][j] = other.matrix[i][j];
        }
    }
    return grid;
}

bool Matrix::compareMatrix(const Matrix &other) {
    if (this->sizeX != other.sizeX || this->sizeY != other.sizeY) return false;

    for (int i = 0; i < this->sizeY; ++i) {
        for (int j = 0; j < this->sizeX; ++j) {
            if (!Helper::compareFloat(this->matrix[i][j], other.matrix[i][j])) {
//                std::cout << "failed at i: " << i << " j: " << j << "   ->   computed: " << std::to_string(this->matrix[i][j]) << " == manual: " << std::to_string(other.matrix[i][j]) << std::endl;
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
    double temp[4];

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

double Matrix::determinant() {
    if (this->sizeX <= 2 && this->sizeY <= 2) {
        return this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] * this->matrix[1][0];
    } else {
        double determinant = 0;
        for (int i = 0; i < this->sizeX; ++i) {
            determinant += cofactor(0, i) * this->matrix[0][i]; //Holy fuck that's an impressive recursion loop
        }
        return determinant;
    }
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

double Matrix::minor(int row, int column) {
    return submatrix(row, column).determinant();
}

double Matrix::cofactor(int row, int column) {
    double minor = this->minor(row, column);
    return ((row + column) % 2) ? -minor : minor;
}

bool Matrix::isInvertible() {
    return determinant() != 0;
}

Matrix Matrix::inverse() {
    Matrix inverse(this->sizeY, this->sizeX);

    double determinant = this->determinant();
    for (int i = 0; i < this->sizeY; ++i) {
        for (int j = 0; j < this->sizeX; ++j) {
            inverse[j][i] = this->cofactor(i, j) / determinant;
        }
    }

    return inverse;
}

void Matrix::setToIdentityMatrix() {
    for (int i = 0; i < sizeX; ++i) {
        this->matrix[i][i] = 1;
    }
}

std::string Matrix::toString() {
    std::string string = "\n";

    for (int i = 0; i < sizeY; ++i) {
        for (int j = 0; j < sizeX; ++j) {
            string.append(" | ");
            string.append((matrix[i][j] > -0) ? " " : "");
            string.append(std::to_string(matrix[i][j]));
        }
        string.append("|\n");
    }
    string.append("\n");

    return string;
}
