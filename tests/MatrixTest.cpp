//
// Created by Max on 2021-01-03.
//

#include "../raytracer/features/Matrix/Matrix.h"
#include "gtest/gtest.h"

TEST(MatrixTests, TestReadWrite) {
    Matrix matrix(4, 4);

    matrix[0][0] = 1;
    matrix[1][0] = 5.5;
    matrix[1][1] = 6.5;

    ASSERT_EQ(1, matrix[0][0]);
    ASSERT_EQ(5.5, matrix[1][0]);
    ASSERT_EQ(6.5, matrix[1][1]);
}

TEST(MatrixTests, TestMatrixSizes) {
    Matrix matrix2(2, 2);

    matrix2[0][0] = -3;
    matrix2[1][0] = 1;
    matrix2[1][1] = -2;

    ASSERT_EQ(-3, matrix2[0][0]);
    ASSERT_EQ(1, matrix2[1][0]);
    ASSERT_EQ(-2, matrix2[1][1]);

    Matrix matrix3(3, 3);

    matrix3[0][0] = -3;
    matrix3[1][1] = -2;
    matrix3[2][2] = 1;

    ASSERT_EQ(-3, matrix3[0][0]);
    ASSERT_EQ(-2, matrix3[1][1]);
    ASSERT_EQ(1, matrix3[2][2]);
}

TEST(MatrixTests, TestEquality) {
    Matrix matrixA(3, 3);
    Matrix matrixB(3, 3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matrixA[i][j] = i + j;
            matrixB[i][j] = i + j + 0.0000001;
        }
    }

    ASSERT_TRUE(matrixA == matrixB);

    matrixB[0][0] = -1;

    ASSERT_FALSE(matrixA == matrixB);
}