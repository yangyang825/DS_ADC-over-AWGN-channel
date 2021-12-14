#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "const.h"
#include "complex.h"

double CNR;
int Eb_N0;
//	loop: 重复次数； Eb_N0：1bit含量的信号的能量 与 噪音密度的比值
int transmitted_bit[BITN], received_bit[BITN];

Complex modulated_signal[POINT_N], transmitted_signal[OFDM_N + GI];
Complex received_signal[OFDM_N];
//Complex H1[OFDM_N * 5 / 4],H2[OFDM_N * 5 / 4];

double estimated_signal[OFDM_N];

double SSE = 0;
double MSE = 0;

int main()
{
	double *ADC_output;
	ADC_output = (double*)malloc(sizeof(double)*OFDM_N);

	srand((unsigned)time(NULL));//rand函数必备，生成随机数
	
	for(Eb_N0=7; Eb_N0<12; Eb_N0++)
	{
		CNR = (double)Eb_N0 + 3.0;
		for(int loop=0; loop<LOOPN; loop++)
		{
			transmitter(transmitted_bit, modulated_signal);
			
			oversampling_GI(modulated_signal, transmitted_signal);
			/* 设置第一个已知的讯号, 此时设置在了时域上, 因为flatfading不管时域频域都是乘法 */
			transmitted_signal[0].real = pilot_real;
			transmitted_signal[0].image = pilot_image;
			
			awgn(transmitted_signal, transmitted_signal);
			flat_fading(transmitted_signal, transmitted_signal);
			//freSel_fading(transmitted_signal, H1,H2, transmitted_signal);
			removeGI(transmitted_signal,received_signal);
			ADC(received_signal, estimated_signal);
			for (int i = 0; i < OFDM_N; i++)
			{
				//printf("i= %d, ADC前的信号的实部%lf, ADC后信号%lf \n", i, received_signal[i].real, estimated_signal[i]);
				SSE += pow((estimated_signal[i] - received_signal[i].real), 2);
			}
			FFT_demodulation(estimated_signal, received_bit);
			
			ber(loop, transmitted_bit, received_bit);
		 }
		
		MSE = SSE / (OFDM_N* LOOPN);
		//printf("MSE %10.8f\n", MSE);
		//printf("111");
	}
    return 0;
}

