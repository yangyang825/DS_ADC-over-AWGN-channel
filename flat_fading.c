#include "const.h"
#include "complex.h"

double uniform01();
double uniform2PI();
void Doppler(Complex(*h));
void setPopagation(Complex(*H));

void flat_fading(Complex(*input), Complex(*output))
{
    Complex H[OFDM_N]; 
	Doppler(H);
	setPopagation(H);//用于设置H=绝对值+0j的形式,以适用传oversampling的IF讯号
	int n;
	for (n=0; n<OFDM_N; n++){
		//printf("flat_fading信道中的H为: %d %lf + %lf\n", n, H[n].real, H[n].image);
		//printf("i= %d, fading前的信号%lf + %lf j\n", n, input[n].real, input[n].image);
        output[n] = ComplexMulti(input[n], H[n]);
        //printf("i= %d, add fading后的信号%lf + %lf j\n", n, output[n].real, output[n].image);
	}
	//printf("flat_fading信道中的0号真实H为:%lf + %lf\n", H[0].real, H[0].image);
}

double uniform2PI()
{
	double theta;
	theta = 2*PI*(double)rand()/RAND_MAX;
	return theta;
}

void setPopagation(Complex(*H)) {
	int j;
	for (j=0; j<OFDM_N; j++)
    {
        H[j].real = Modules(H[j]);
        H[j].image = 0;
    }
}
void Doppler(Complex(*h))
{
    Complex An;
    Complex hn[OFDM_N];
    double thetan, phin;
    int n, m, i, j;
    double u1, u2;

	double power = 1.0/8.0; //A的模，分量个数改变那么每个分量的power也变化
    for (m=0; m<OFDM_N; m++)
    {
        h[m].image = 0;
        h[m].real = 0;
    }


    for (n = 0; n < 8; n++)
    {
        thetan = uniform2PI();
        phin = uniform2PI();
        u1 = uniform01();
        u2 = uniform01();
        An.real = sqrt(-(power)* log(u1)) * cos(2 * PI * u2);
        An.image = sqrt(-(power) * log(u1)) * sin(2 * PI * u2);
        for (i=0; i<OFDM_N; i++)
        {
            hn[i] = ComplexMulti(An, Exp(2 * PI * Fd * cos(thetan) * i * Ts + phin));
        }
        for (j=0; j<OFDM_N; j++)
        {
            h[j].real += hn[j].real;
            h[j].image += hn[j].image;
        }
    }
}
