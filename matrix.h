#pragma once

void MatrixSubMatrixToMatrix(double (*a)[DIM], double (*b)[DIM], double (*c)[DIM]);

void MatrixAddMatrixToMatrix(double (*a)[DIM], double (*b)[DIM], double (*c)[DIM]);

void MatrixMulMatrixToMatrix(double (*a)[DIM], double (*b)[DIM], double (*c)[DIM]);

void MatrixMulVectorToVector(double (*a)[DIM], double(*v1), double(*v2));

void ScalarMulMatrixToMatrix(double s, double (*a)[DIM], double (*c)[DIM]);

void VectorMulVectorToScalar(double(*v1), double(*v2), double(*s));

void VectorAddVectorToVector(double(*v1), double(*v2), double(*v3));

void VectorMulMatrixToVector(double(*v1), double (*a)[DIM], double(*v2));

void VectorMulVectorToMatrix(double(*v1), double(*v2), double (*a)[DIM]);

void ScalarMulVectorToVector(double s, double(*v1), double(*v2));
