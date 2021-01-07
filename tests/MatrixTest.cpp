//
// Created by Max on 2021-01-03.
//

#include "../raytracer/features/Helper.h"
#include "../raytracer/features/Matrix/Matrices.h"
#include "gtest/gtest.h"

void initMatricesMultiplications(Matrix &, Matrix &, Matrix &);

void initMatricesTransposition(Matrix &, Matrix &);

void initSubmatrices(Matrix &, Matrix &, Matrix &, Matrix &);

void initMatricesLargeDeterminant(Matrix &, Matrix &);

void initMatricesInvertibility(Matrix &, Matrix &);

void initMatricesInverse(Matrix &, Matrix &);

void initMatricesInversion(Matrix &, Matrix &, Matrix &, Matrix &);

void initCancelMultiply(Matrix &, Matrix &);

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

TEST(MatrixTests, TestMultipliation) {
    Matrix matrixA(4, 4);
    Matrix matrixB(4, 4);
    Matrix matrixResult(4, 4);

    initMatricesMultiplications(matrixA, matrixB, matrixResult);

    ASSERT_TRUE(matrixResult == matrixA * matrixB);
}

void initMatricesMultiplications(Matrix &matrixA, Matrix &matrixB, Matrix &matrixC) {
    float rowA1[] = {1, 2, 3, 4};
    float rowA2[] = {5, 6, 7, 8};
    float rowA3[] = {9, 8, 7, 6};
    float rowA4[] = {5, 4, 3, 2};
    std::copy(rowA1, rowA1 + 4, matrixA[0]);
    std::copy(rowA2, rowA2 + 4, matrixA[1]);
    std::copy(rowA3, rowA3 + 4, matrixA[2]);
    std::copy(rowA4, rowA4 + 4, matrixA[3]);

    float rowB1[] = {-2, 1, 2, 3};
    float rowB2[] = {3, 2, 1, -1};
    float rowB3[] = {4, 3, 6, 5};
    float rowB4[] = {1, 2, 7, 8};
    std::copy(rowB1, rowB1 + 4, matrixB[0]);
    std::copy(rowB2, rowB2 + 4, matrixB[1]);
    std::copy(rowB3, rowB3 + 4, matrixB[2]);
    std::copy(rowB4, rowB4 + 4, matrixB[3]);

    float rowC1[] = {20, 22, 50, 48};
    float rowC2[] = {44, 54, 114, 108};
    float rowC3[] = {40, 58, 110, 102};
    float rowC4[] = {16, 26, 46, 42};
    std::copy(rowC1, rowC1 + 4, matrixC[0]);
    std::copy(rowC2, rowC2 + 4, matrixC[1]);
    std::copy(rowC3, rowC3 + 4, matrixC[2]);
    std::copy(rowC4, rowC4 + 4, matrixC[3]);
}

TEST(MatrixTests, TestTupleMultiplication) {
    Tuple tuple(1, 2, 3, 1);
    Matrix matrix(4, 4);

    float rowA1[] = {1, 2, 3, 4};
    float rowA2[] = {2, 4, 4, 2};
    float rowA3[] = {8, 6, 4, 1};
    float rowA4[] = {0, 0, 0, 1};
    std::copy(rowA1, rowA1 + 4, matrix[0]);
    std::copy(rowA2, rowA2 + 4, matrix[1]);
    std::copy(rowA3, rowA3 + 4, matrix[2]);
    std::copy(rowA4, rowA4 + 4, matrix[3]);

    ASSERT_TRUE(Tuple(18, 24, 33, 1) == matrix * tuple);
}

TEST(MatrixTests, TestIdentityMatrix) {
    Matrix matrix(4, 4);
    Tuple tuple(1, 2, 3, 4);
    Matrix identity = Matrix::identityMatrix();

    float rowA1[] = {0, 1, 2, 4};
    float rowA2[] = {1, 2, 4, 8};
    float rowA3[] = {2, 4, 8, 16};
    float rowA4[] = {4, 8, 16, 32};
    std::copy(rowA1, rowA1 + 4, matrix[0]);
    std::copy(rowA2, rowA2 + 4, matrix[1]);
    std::copy(rowA3, rowA3 + 4, matrix[2]);
    std::copy(rowA4, rowA4 + 4, matrix[3]);

    ASSERT_TRUE(matrix == matrix * identity);
    ASSERT_TRUE(tuple == identity * tuple);
}

TEST(MatrixTests, TestTransposition) {
    Matrix matrixA(4, 4);
    Matrix result(4, 4);

    initMatricesTransposition(matrixA, result);

    ASSERT_TRUE(matrixA.transpose() == result);
    ASSERT_TRUE(Matrix::identityMatrix() == Matrix::identityMatrix().transpose());
}

void initMatricesTransposition(Matrix &matrixA, Matrix &matrixB) {
    float rowA1[] = {0, 9, 3, 0};
    float rowA2[] = {9, 8, 0, 8};
    float rowA3[] = {1, 8, 5, 3};
    float rowA4[] = {0, 0, 5, 8};
    std::copy(rowA1, rowA1 + 4, matrixA[0]);
    std::copy(rowA2, rowA2 + 4, matrixA[1]);
    std::copy(rowA3, rowA3 + 4, matrixA[2]);
    std::copy(rowA4, rowA4 + 4, matrixA[3]);

    float rowB1[] = {0, 9, 1, 0};
    float rowB2[] = {9, 8, 8, 0};
    float rowB3[] = {3, 0, 5, 5};
    float rowB4[] = {0, 8, 3, 8};
    std::copy(rowB1, rowB1 + 4, matrixB[0]);
    std::copy(rowB2, rowB2 + 4, matrixB[1]);
    std::copy(rowB3, rowB3 + 4, matrixB[2]);
    std::copy(rowB4, rowB4 + 4, matrixB[3]);
}

TEST(MatrixTests, TestDeterminant) {
    Matrix matrix(2, 2);
    matrix[0][0] = 1;
    matrix[0][1] = 5;
    matrix[1][0] = -3;
    matrix[1][1] = 2;

    ASSERT_EQ(17, matrix.determinant());
}

TEST(MatrixTests, TestSubmatrices) {
    Matrix matrixA(3, 3);
    Matrix resultA(2, 2);
    Matrix matrixB(4, 4);
    Matrix resultB(3, 3);

    initSubmatrices(matrixA, resultA, matrixB, resultB);

    ASSERT_TRUE(resultA == matrixA.submatrix(0, 2));
    ASSERT_TRUE(resultB == matrixB.submatrix(2, 1));
}

void initSubmatrices(Matrix &matrixA, Matrix &resultA, Matrix &matrixB, Matrix &resultB) {
    float rowA1[] = {1, 5, 0};
    float rowA2[] = {-3, 2, 7};
    float rowA3[] = {0, 6, -3};
    std::copy(rowA1, rowA1 + 3, matrixA[0]);
    std::copy(rowA2, rowA2 + 3, matrixA[1]);
    std::copy(rowA3, rowA3 + 3, matrixA[2]);

    float rowRA1[] = {-3, 2};
    float rowRA2[] = {0, 6};
    std::copy(rowRA1, rowRA1 + 2, resultA[0]);
    std::copy(rowRA2, rowRA2 + 2, resultA[1]);

    float rowB1[] = {-6, 1, 1, 6};
    float rowB2[] = {-8, 5, 8, 6};
    float rowB3[] = {-1, 0, 8, 2};
    float rowB4[] = {-7, 1, -1, 1};
    std::copy(rowB1, rowB1 + 4, matrixB[0]);
    std::copy(rowB2, rowB2 + 4, matrixB[1]);
    std::copy(rowB3, rowB3 + 4, matrixB[2]);
    std::copy(rowB4, rowB4 + 4, matrixB[3]);

    float rowRB1[] = {-6, 1, 6};
    float rowRB2[] = {-8, 8, 6};
    float rowRB3[] = {-7, -1, 1};
    std::copy(rowRB1, rowRB1 + 3, resultB[0]);
    std::copy(rowRB2, rowRB2 + 3, resultB[1]);
    std::copy(rowRB3, rowRB3 + 3, resultB[2]);
}

TEST(MatrixTests, TestMinor) {
    Matrix matrixA(3, 3);

    float rowA1[] = {3, 5, 0};
    float rowA2[] = {2, -1, -7};
    float rowA3[] = {6, -1, 5};
    std::copy(rowA1, rowA1 + 3, matrixA[0]);
    std::copy(rowA2, rowA2 + 3, matrixA[1]);
    std::copy(rowA3, rowA3 + 3, matrixA[2]);

    ASSERT_EQ(25, matrixA.submatrix(1, 0).determinant());
    ASSERT_EQ(25, matrixA.minor(1, 0));
}

TEST(MatrixTests, TestCofactor) {
    Matrix matrixA(3, 3);

    float rowA1[] = {3, 5, 0};
    float rowA2[] = {2, -1, -7};
    float rowA3[] = {6, -1, 5};
    std::copy(rowA1, rowA1 + 3, matrixA[0]);
    std::copy(rowA2, rowA2 + 3, matrixA[1]);
    std::copy(rowA3, rowA3 + 3, matrixA[2]);

    ASSERT_EQ(-12, matrixA.minor(0, 0));
    ASSERT_EQ(-12, matrixA.cofactor(0, 0));
    ASSERT_EQ(25, matrixA.minor(1, 0));
    ASSERT_EQ(-25, matrixA.cofactor(1, 0));
}

TEST(MatrixTests, TestLargeDeterminant) {
    Matrix matrixA(3, 3);
    Matrix matrixB(4, 4);

    initMatricesLargeDeterminant(matrixA, matrixB);

    ASSERT_EQ(56, matrixA.cofactor(0, 0));
    ASSERT_EQ(12, matrixA.cofactor(0, 1));
    ASSERT_EQ(-46, matrixA.cofactor(0, 2));
    ASSERT_EQ(-196, matrixA.determinant());

    ASSERT_EQ(690, matrixB.cofactor(0, 0));
    ASSERT_EQ(447, matrixB.cofactor(0, 1));
    ASSERT_EQ(210, matrixB.cofactor(0, 2));
    ASSERT_EQ(51, matrixB.cofactor(0, 3));
    ASSERT_EQ(-4071, matrixB.determinant());
}

void initMatricesLargeDeterminant(Matrix& matrixA, Matrix& matrixB) {
    float rowA1[] = {1, 2, 6};
    float rowA2[] = {-5, 8, -4};
    float rowA3[] = {2, 6, 4};
    std::copy(rowA1, rowA1 + 3, matrixA[0]);
    std::copy(rowA2, rowA2 + 3, matrixA[1]);
    std::copy(rowA3, rowA3 + 3, matrixA[2]);

    float rowB1[] = {-2, -8, 3, 5};
    float rowB2[] = {-3, 1, 7, 3};
    float rowB3[] = {1, 2, -9, 6};
    float rowB4[] = {-6, 7, 7, -9};
    std::copy(rowB1, rowB1 + 4, matrixB[0]);
    std::copy(rowB2, rowB2 + 4, matrixB[1]);
    std::copy(rowB3, rowB3 + 4, matrixB[2]);
    std::copy(rowB4, rowB4 + 4, matrixB[3]);
}

TEST(MatrixTests, TestMatrixInvertibility) {
    Matrix matrixA(4, 4);
    Matrix matrixB(4, 4);

    initMatricesInvertibility(matrixA, matrixB);

    ASSERT_EQ(-2120, matrixA.determinant());
    ASSERT_TRUE(matrixA.isInvertible());

    ASSERT_EQ(0, matrixB.determinant());
    ASSERT_FALSE(matrixB.isInvertible());
}

void initMatricesInvertibility(Matrix& matrixA, Matrix& matrixB) {
    float rowA1[] = {6, 4, 4, 4};
    float rowA2[] = {5, 5, 7, 6};
    float rowA3[] = {4, -9, 3, -7};
    float rowA4[] = {9, 1, 7, -6};
    std::copy(rowA1, rowA1 + 4, matrixA[0]);
    std::copy(rowA2, rowA2 + 4, matrixA[1]);
    std::copy(rowA3, rowA3 + 4, matrixA[2]);
    std::copy(rowA4, rowA4 + 4, matrixA[3]);

    float rowB1[] = {-4, 2, -2, -3};
    float rowB2[] = {9, 6, 2, 6};
    float rowB3[] = {0, -5, 1, -5};
    float rowB4[] = {0, 0, 0, 0};
    std::copy(rowB1, rowB1 + 4, matrixB[0]);
    std::copy(rowB2, rowB2 + 4, matrixB[1]);
    std::copy(rowB3, rowB3 + 4, matrixB[2]);
    std::copy(rowB4, rowB4 + 4, matrixB[3]);
}

TEST(MatrixTests, TestMatrixInverse) {
    Matrix matrixA(4, 4);
    Matrix result(4, 4);

    initMatricesInverse(matrixA, result);

    Matrix inverse = matrixA.inverse();

    ASSERT_EQ(532, matrixA.determinant());
    ASSERT_EQ(-160, matrixA.cofactor(2, 3));
    ASSERT_TRUE(Helper::compareFloat((-160 / 532.0), inverse[3][2])) << "actual value: " << inverse[3][2];
    ASSERT_EQ(105, matrixA.cofactor(3, 2));
    ASSERT_TRUE(Helper::compareFloat((105 / 532.0), inverse[2][3]));
    ASSERT_TRUE(inverse == result);
}

void initMatricesInverse(Matrix& matrixA, Matrix& matrixB) {
    float rowA1[] = {-5, 2, 6, -8};
    float rowA2[] = {1, -5, 1, 8};
    float rowA3[] = {7, 7, -6, -7};
    float rowA4[] = {1, -3, 7, 4};
    std::copy(rowA1, rowA1 + 4, matrixA[0]);
    std::copy(rowA2, rowA2 + 4, matrixA[1]);
    std::copy(rowA3, rowA3 + 4, matrixA[2]);
    std::copy(rowA4, rowA4 + 4, matrixA[3]);

    float rowB1[] = {0.21805, 0.45113, 0.24060, -0.04511};
    float rowB2[] = {-0.80827, -1.45677, -0.44361,  0.52068};
    float rowB3[] = {-0.07895, -0.22368, -0.05263,  0.19737};
    float rowB4[] = {-0.52256, -0.81391, -0.30075,  0.30639};
    std::copy(rowB1, rowB1 + 4, matrixB[0]);
    std::copy(rowB2, rowB2 + 4, matrixB[1]);
    std::copy(rowB3, rowB3 + 4, matrixB[2]);
    std::copy(rowB4, rowB4 + 4, matrixB[3]);
}

TEST(MatrixTests, TestMatrixInversion) {
    Matrix matrixA(4, 4);
    Matrix inverseA(4, 4);
    Matrix matrixB(4, 4);
    Matrix inverseB(4, 4);

    initMatricesInversion(matrixA, inverseA, matrixB, inverseB);

    ASSERT_TRUE(matrixA.inverse() == inverseA);
    ASSERT_TRUE(matrixB.inverse() == inverseB);
}

void initMatricesInversion(Matrix& matrixA, Matrix& resultA, Matrix& matrixB, Matrix& resultB) {
    float rowA1[] = {8, -5, 9, 2};
    float rowA2[] = {7, 5, 6, 1};
    float rowA3[] = {-6, 0, 9, 6};
    float rowA4[] = {-3, 0, -9, -4};
    std::copy(rowA1, rowA1 + 4, matrixA[0]);
    std::copy(rowA2, rowA2 + 4, matrixA[1]);
    std::copy(rowA3, rowA3 + 4, matrixA[2]);
    std::copy(rowA4, rowA4 + 4, matrixA[3]);

    float rowRA1[] = {-0.15385, -0.15385, -0.28205, -0.53846};
    float rowRA2[] = {-0.07692,  0.12308,  0.02564,  0.03077};
    float rowRA3[] = {0.35897,  0.35897,  0.43590,  0.92308};
    float rowRA4[] = {-0.69231, -0.69231, -0.76923, -1.92308};
    std::copy(rowRA1, rowRA1 + 4, resultA[0]);
    std::copy(rowRA2, rowRA2 + 4, resultA[1]);
    std::copy(rowRA3, rowRA3 + 4, resultA[2]);
    std::copy(rowRA4, rowRA4 + 4, resultA[3]);

    float rowB1[] = {9, 3, 0, 9};
    float rowB2[] = {-5, -2, -6, -3};
    float rowB3[] = {-4, 9, 6, 4};
    float rowB4[] = {-7, 6, 6, 2};
    std::copy(rowB1, rowB1 + 4, matrixB[0]);
    std::copy(rowB2, rowB2 + 4, matrixB[1]);
    std::copy(rowB3, rowB3 + 4, matrixB[2]);
    std::copy(rowB4, rowB4 + 4, matrixB[3]);

    float rowRB1[] = {-0.04074, -0.07778,  0.14444, -0.22222};
    float rowRB2[] = {-0.07778,  0.03333,  0.36667, -0.33333};
    float rowRB3[] = {-0.02901, -0.14630, -0.10926,  0.12963};
    float rowRB4[] = {0.17778,  0.06667, -0.26667,  0.33333};
    std::copy(rowRB1, rowRB1 + 4, resultB[0]);
    std::copy(rowRB2, rowRB2 + 4, resultB[1]);
    std::copy(rowRB3, rowRB3 + 4, resultB[2]);
    std::copy(rowRB4, rowRB4 + 4, resultB[3]);
}

TEST(MatrixTests, TestCancelMultiply) {
    Matrix matrixA(4, 4);
    Matrix matrixB(4, 4);

    initCancelMultiply(matrixA, matrixB);

    Matrix matrixC = matrixA * matrixB;

    ASSERT_TRUE(matrixC * matrixB.inverse() == matrixA);
}

void initCancelMultiply(Matrix& matrixA, Matrix& matrixB) {
    float rowA1[] = {3, -9, 7, 3};
    float rowA2[] = {3, -8, 2, -9};
    float rowA3[] = {-4, 4, 4, 1};
    float rowA4[] = {-6, 5, -1, 1};
    std::copy(rowA1, rowA1 + 4, matrixA[0]);
    std::copy(rowA2, rowA2 + 4, matrixA[1]);
    std::copy(rowA3, rowA3 + 4, matrixA[2]);
    std::copy(rowA4, rowA4 + 4, matrixA[3]);

    float rowB1[] = {8, 2, 2, 2};
    float rowB2[] = {3, -1, 7, 0};
    float rowB3[] = {7, 0, 5, 4};
    float rowB4[] = {6, -2, 0, 5};
    std::copy(rowB1, rowB1 + 4, matrixB[0]);
    std::copy(rowB2, rowB2 + 4, matrixB[1]);
    std::copy(rowB3, rowB3 + 4, matrixB[2]);
    std::copy(rowB4, rowB4 + 4, matrixB[3]);
}
