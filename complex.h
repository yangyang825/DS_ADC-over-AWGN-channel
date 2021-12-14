#pragma once


//定义复数结构，a+bj=real+image*j 
typedef struct {
    double real, image;
}Complex;


Complex initComplex(double real, double image);

Complex ComplexAdd(Complex a, Complex b); //复数加法 

Complex ComplexMinus(Complex a, Complex b);	// 复数减法

Complex ComplexMulti(Complex a, Complex b);	//复数乘法

Complex  ComplexConjugate(Complex a);	//复数乘法 

Complex Exp(double phi);	//e^jφ,复数的指数形式

double Modules(Complex a); 	//复数求模
