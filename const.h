#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "complex.h"

#ifndef const_h
#define const_h
#endif /* const_h */

/*---------------------------------------------------------*/
/* Parameters                                              */
/*---------------------------------------------------------*/

#define LOOPN		100000
/*----------����----------*/
#define sqr(x)				((x)*(x))
#define DIM			100

/*----------transmitter----------*/
#define POINT_N		(64) //�ź�����
#define BITN		(POINT_N * 2)		//QPSK���ƣ��źŶ�Ӧ��bit����Ϊ�ź���������
#define PI			3.141592654		//acos(-1.0)
#define OneBySqrt2	0.7071067812	//1.0/sqrt(2.0)
/*----------����OFDM�ź�----------*/
#define	GI			0//(POINT_N/4)//16				/* Guard interval */
#define subcar_N	1024				//FFT�źŸ���
#define OFDM_N     	(subcar_N)//1024          //OFDM�źŸ���
#define trans_N		(OFDM_N+GI)//1024+16
#define pilot_real  1//pilot�źŵ�������ҪΪ1,���򲻹�ƽ 
#define pilot_image 0
/*----------freSel_fading----------*/
#define ORIGINALTHETA         0
#define Fd                    0
#define D                     2
/*................��ͳһ���ű�ʾ...................*/
#define SYMBOL_RATE			42.0e3
#define Ts					(1.0/SYMBOL_RATE)
#define fs2					1024000/Ts
#define fs1					Ts/OFDM_N







#define Vref  (1.0);	//|Vref|>Math.max(received_signal[i].real)
/*----------statistic/ber----------*/
#define FILENAME			".\\data\\awgn.dat"



/*---------------------------------------------------------*/
/* Subfunctions                                            */
/*---------------------------------------------------------*/

/*----------Transmitter----------*/
void transmitter(int(*bit), Complex(*signal));

void oversampling_GI(Complex(*modulated_signal), Complex(*transmitted_signal));

void awgn(Complex(*input_signal), Complex(*output_signal));

void flat_fading(Complex(*input), Complex(*output));

//void freSel_fading(Complex(*input), Complex(*H1), Complex(*H2), Complex(*output));

void removeGI(Complex(*signal), Complex(*output_signal));

void ADC(Complex(*received_signal),double(*estimated_signal));

void FFT_demodulation(double(*estimated_signal), int(*received_bit));

void ber(int loop, int(*tbit), int(*rbit));
