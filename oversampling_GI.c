#include "const.h"
#include "complex.h"

//Complex modulated_signal[POINT_N], transmitted_signal[OFDM_N];
//POINT_N代表OFDM的subcarriers中,携带data的subcarriers的数量; OFDM_N代表所有subcarriers即FFT信号数量 
//用过采样原理对调制信号在频域上做IFFT,获得高频的OFDM信号 

void overSampling(Complex(*modulated_signal), Complex(*conjugate_signal), Complex(*OFDM_signal));
void addGI(Complex (*OFDM_signal), Complex(*transmitted_signal));

void oversampling_GI (Complex (*modulated_signal),  Complex(*transmitted_signal))
{
    Complex *OFDM_signal;
    OFDM_signal = (Complex*)malloc(sizeof(Complex) * OFDM_N);
    for (int i = 0; i < OFDM_N; i++) {
        OFDM_signal[i].real = 0;
        OFDM_signal[i].image = 0;
    }
    Complex* conjugate_signal;
    conjugate_signal = (Complex*)malloc(sizeof(Complex) * POINT_N);

    // obtain conjugate(s)
    for (int j = 0; j < POINT_N; j++)
    {
        conjugate_signal[j].real = modulated_signal[j].real;
        conjugate_signal[j].image = -modulated_signal[j].image;

    }
    overSampling(modulated_signal, conjugate_signal, OFDM_signal);
    //printf("%lf\n", OFDM_signal[0]);
    addGI(OFDM_signal, transmitted_signal);
}
//	overSampling
void overSampling (Complex (*modulated_signal), Complex(*conjugate_signal),Complex (*OFDM_signal))
{
    
	//mapping
    Complex* FFT_signal;
    FFT_signal = (Complex*)malloc(sizeof(Complex) * subcar_N);
    //Complex FFT_signal[subcar_N];//1024个subcarriers(FFT信号),其中2*POINT_N个会搭载data 
    for (int i = 0; i < subcar_N; i++) {
        FFT_signal[i].real = 0;
        FFT_signal[i].image = 0;
    }
    //OVERSAMPLING步骤1：把POINT_N放到subcar_N的一边中间位置，然后对称位置为共轭，以满足oversampling条件；最后其他部分补0 
    for (int k = 0; k < POINT_N; k++)
    {
    	FFT_signal[k+100+(subcar_N/2)] = modulated_signal[k];//[~512~] 512+0+100
    	FFT_signal[-k-100+(subcar_N / 2)] = conjugate_signal[k];
        
	}
  
    Complex* temp_signal;
    temp_signal = (Complex*)malloc(sizeof(Complex) * subcar_N);
    for (int i = 0; i < subcar_N; i++) {
        temp_signal[i].real = 0;
        temp_signal[i].image = 0;
    }
	for (int k = 0; k < OFDM_N; k++)	
    {
    	for (int n = 0; n < subcar_N; n++)//1024=subcar_N=OFDM_N
    	{
            temp_signal[k].real = 1 / sqrt(OFDM_N) * ComplexMulti(FFT_signal[n], Exp(2 * PI * k * n / OFDM_N)).real;
            temp_signal[k].image = 1 / sqrt(OFDM_N) * ComplexMulti(FFT_signal[n], Exp(2 * PI * k * n / OFDM_N)).image;
		
		    OFDM_signal[k].real = OFDM_signal[k].real + temp_signal[k].real;
		    OFDM_signal[k].image = OFDM_signal[k].image + temp_signal[k].image;
    	}
	}
    
    
}

void addGI(Complex(*OFDM_signal), Complex(*transmitted_signal))
{
	int n;
	for (n = 0; n < GI; n++)
    {
        transmitted_signal[n] = OFDM_signal[n + GI*3];
    }
    for (n = GI; n < OFDM_N; n++)
    {
        transmitted_signal[n] = OFDM_signal[n - GI];
    }
}

