#include "const.h"
#include "matrix.h"
#include <math.h>

void MatrixSubMatrixToMatrix(double (*a)[DIM], double (*b)[DIM], double (*c)[DIM])
{
  int i, j;
  for (i = 0; i < DIM; i++)
    for (j = 0; j < DIM; j++)
    {
      c[i][j] = a[i][j] - b[i][j];
    }
}

void MatrixAddMatrixToMatrix(double (*a)[DIM], double (*b)[DIM], double (*c)[DIM])
{
  int i, j;
  for (i = 0; i < DIM; i++)
    for (j = 0; j < DIM; j++)
    {
      c[i][j] = a[i][j] + b[i][j];
    }
}

void MatrixMulMatrixToMatrix(double (*a)[DIM], double (*b)[DIM],
                             double (*c)[DIM])
{
  int i, j, k;
  double sum;
  for (i = 0; i < DIM; i++)
  {
    for (j = 0; j < DIM; j++)
    {
      sum = 0.0;
      for (k = 0; k < DIM; k++)
      {
        sum += (a[i][k] * b[k][j]);
      }
      c[i][j] = sum;
    }
  }
}

void MatrixMulVectorToVector(double (*a)[DIM], double(*v1), double(*v2))
{
  int i, j;
  double sum;
  for (i = 0; i < DIM; i++)
  {
    sum = 0.0;
    for (j = 0; j < DIM; j++)
    {
      sum += (a[i][j] * v1[j]);
    }
    v2[i] = sum;
  }
}

void ScalarMulMatrixToMatrix(double s, double (*a)[DIM], double (*c)[DIM])
{
  int i, j;
  for (i = 0; i < DIM; i++)
  {
    for (j = 0; j < DIM; j++)
    {
      c[i][j] = s * a[i][j];
    }
  }
}

void VectorMulVectorToScalar(double(*v1), double(*v2), double(*s))
{
  int i;
  *s = 0.0;
  for (i = 0; i < DIM; i++)
  {
    *s += (v1[i] * v2[i]);
  }
}

void VectorAddVectorToVector(double(*v1), double(*v2), double(*v3))
{
  int i;
  for (i = 0; i < DIM; i++)
  {
    v3[i] = v1[i] + v2[i];
  }
}

void VectorMulMatrixToVector(double(*v1), double (*a)[DIM], double(*v2))
{
  int i, j;
  for (i = 0; i < DIM; i++)
  {
    v2[i] = 0.0;
    for (j = 0; j < DIM; j++)
    {
      v2[i] += v1[j] * a[j][i];
    }
  }
}

void VectorMulVectorToMatrix(double(*v1), double(*v2), double (*a)[DIM])
{
  int i, j;
  for (i = 0; i < DIM; i++)
  {
    for (j = 0; j < DIM; j++)
    {
      a[i][j] = v1[i] * v2[j];
    }
  }
}

void ScalarMulVectorToVector(double s, double(*v1), double(*v2))
{
  int i;
  for (i = 0; i < DIM; i++)
  {
    v2[i] = s * v1[i];
  }
}
