#pragma once


void MatrixSubMatrixToMatrix(double(*a)[DIM], double(*b)[DIM], double(*c)[DIM]);  /* 方形矩阵的减法C[n*n]=A[n*n]-B[n*n] */

void MatrixAddMatrixToMatrix(double(*a)[DIM], double(*b)[DIM], double(*c)[DIM]); /* 方形矩阵的加法*/

void MatrixMulMatrixToMatrix(double(*a)[DIM], double(*b)[DIM], double(*c)[DIM]); /* 方形矩阵的乘法*/

void MatrixMulVectorToVector(double(*a)[DIM], double(*v1), double(*v2)); /* 方形矩阵*列向量=列向量 */
 
void ScalarMulMatrixToMatrix(double s, double(*a)[DIM], double(*c)[DIM]); /* 标量*方形矩阵=方形矩阵*/

void VectorMulVectorToScalar(double(*v1), double(*v2), double(*s)); /*行向量*列向量=标量*/

void VectorAddVectorToVector(double(*v1), double(*v2), double(*v3)); /*行向量+行向量 */

void VectorMulMatrixToVector(double(*v1), double(*a)[DIM], double(*v2)); /*行向量*方形矩阵=行向量*/

void VectorMulVectorToMatrix(double(*v1), double(*v2), double(*a)[DIM]); /* 列向量*行向量=方形矩阵 */

void ScalarMulVectorToVector(double s, double(*v1), double(*v2)); /*标量*行向量 */
