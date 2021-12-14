#include "const.h"
#include "complex.h"
#include <math.h>

Complex initComplex(double real, double image)
{
    Complex Z;
    Z.image = image;
    Z.real = real;
    return Z;
}

Complex ComplexAdd(Complex a, Complex b) {
    Complex z;
    z.real = a.real + b.real;
    z.image = a.image + b.image;
    return z;
}

Complex ComplexMinus(Complex a, Complex b) {
    Complex z;
    z.real = a.real - b.real;
    z.image = a.image - b.image;
    return z;
}

Complex ComplexMulti(Complex a, Complex b)
{
    Complex Z;
    Z.real = a.real * b.real - a.image * b.image;
    Z.image = a.real * b.image + a.image * b.real;
    return Z;
}
Complex ComplexConjugate(Complex a)
{
    Complex Z;
    Z.real = a.real;
    Z.image = -a.image;
    return Z;
}

Complex Exp(double phi)
{
    Complex Z;
    Z.real = cos(phi);
    Z.image = sin(phi);
    return Z;
}

double Modules(Complex a)
{
    double M;
    M = sqrt(a.real * a.real + a.image * a.image);
    return M;

}
