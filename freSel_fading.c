#include "const.h"

void freSel_fading(Complex(*input), Complex(*H1), Complex(*H2), Complex(*output))
{
 
    Doppler(H1);
    Doppler(H2);
    int i;
    for(i=D;i<(OFDM_N*5/4);i++)
    {
    	printf("i= %d, freSelfading前的信号%lf + %lf j\n", i, input[i].real, input[i].image);
        output[i]=ComplexAdd(ComplexMulti(input[i], H1[i]), ComplexMulti(input[i-D], H2[i-D]));
        //截取 
        printf("i= %d, add freSelfading后的信号%lf + %lf j\n", i, output[i].real, output[i].image);
    }
}

double PHI() {
    static int seed;
    static int flag = 0;
    if (flag == 0) {
        flag = 1;
        srand(time(NULL));
        seed = rand();
    }
    seed = 2045 * seed + 1;
    seed = seed - (seed / 1048576) * 1048576;
    return (seed) * 2 * PI / 1048576.0;


}
double uni() {
    static int seed;
    static int flag = 0;
    if (flag == 0) {
        flag = 1;
        srand(time(NULL));
        seed = rand();
    }
    seed = 2045 * seed + 1;
    seed = seed - (seed / 1048576) * 1048576;
    return (seed) / 1048576.0;

}
//void Doppler(Complex(*h))
//{
//    Complex An;
//    Complex hn[OFDM_N * 5 / 4];
//    double thetan, phin;
//    int n, m, i, j;
//    double u1, u2;
//
//    for (m = 0; m < (OFDM_N * 5 / 4); m++)
//    {
//        h[m].image = 0;
//        h[m].real = 0;
//    }
//
//    for (n = 0; n < 8; n++)
//
//    {
//        thetan = PHI();
//        phin = PHI();
//        u1 = uni();
//        u2 = uni();
//        An.real = sqrt(-(1 / 16.0) * log(u1)) * cos(2 * PI * u2);//...
//        An.image = sqrt(-(1 / 16.0) * log(u1)) * sin(2 * PI * u2);//...
//        for (i = 0; i < (OFDM_N * 5 / 4); i++)
//        {
//            hn[i] = ComplexMulti(An, Exp(2 * PI * Fd * cos(thetan) * i * Ts + phin));
//        }
//        for (j = 0; j < (OFDM_N * 5 / 4); j++)
//        {
//            h[j].real = h[j].real + hn[j].real;
//            h[j].image = h[j].image + hn[j].image;
//        }
//    }
//
//}


