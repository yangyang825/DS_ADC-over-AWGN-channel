#pragma once
typedef struct
{
  double real, image;
} Complex;

Complex initComplex(double real, double image);

Complex ComplexAdd(Complex a, Complex b);

Complex ComplexMinus(Complex a, Complex b);

Complex ComplexMulti(Complex a, Complex b);

Complex ComplexConjugate(Complex a);

Complex Exp(double phi);

double Modules(Complex a);
