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

#define LOOPN 100
/*----------COMPUTATION----------*/
#define sqr(x) ((x) * (x))
#define DIM 100

/*----------TRANSMITTER----------*/
#define POINT_N (64)            // number of modulated QPSK signals
#define BITN (POINT_N * 2)      // QPSK modulation
#define PI 3.141592654          // acos(-1.0)
#define OneBySqrt2 0.7071067812 // 1.0/sqrt(2.0)
/*----------OFDM SYMBOL----------*/
#define GI 0                  //(POINT_N/4)//16				/* Guard interval */
#define subcar_N 1024         // number of FFT points
#define OFDM_N (subcar_N)     // 1024          //number of subcarriers
#define trans_N (OFDM_N + GI) // 1024+16

/*----------freSel_fading----------*/
#define ORIGINALTHETA 0
#define Fd 0
#define D 2
/*...................................*/
#define SYMBOL_RATE 42.0e3
#define Ts (1.0 / SYMBOL_RATE)
#define fs2 1024000 / Ts
#define fs1 Ts / OFDM_N

/*----------------ADC---------------*/
#define Vref (1.0);            //|Vref|>Math.max(received_signal[i].real)
#define SAMPLING_RATE_ADC 5000 // 5//100//5//5//2//10//2// 1
//#define NOISE_ENLARGEMENT	2.3//(power of transmitted signals)/(power of modulated signals)
/*----------------FILTER AND OVERSAMPLING---------------*/
#define CENTER 512                   //
#define DELTASUB 100                 // 0
#define RIGHTSTART CENTER + DELTASUB // from this point, subcarriers on the right side will carry data, [612, 612+63];
#define LEFTSTART CENTER - DELTASUB  // from this point, subcarriers on the left side will carry conjugate data, [412-63, 412];

/*----------statistic/ber----------*/
#define FILENAME ".\\data\\awgn.dat"

/*---------------------------------------------------------*/
/* Subfunctions                                            */
/*---------------------------------------------------------*/
void transmitter(int(*bit), Complex(*signal));
void oversampling_GI(Complex(*modulated_signal), Complex(*transmitted_signal));
void awgn(Complex(*input_signal), Complex(*output_signal));
void removeGI(Complex(*signal), Complex(*output_signal));
void ADC(Complex(*received_signal), Complex(*estimated_signal));
void FFT_demodulation(Complex(*estimated_signal), int(*received_bit));
void ber(int loop, int(*tbit), int(*rbit));
