#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "const.h"
#include "complex.h"

double CNR;
int Eb_N0;
int transmitted_bit[BITN], received_bit[BITN];
Complex modulated_signal[POINT_N], transmitted_signal[OFDM_N + GI];
Complex received_signal[OFDM_N];
Complex estimated_signal[OFDM_N];

double SSE = 0;
double MSE = 0;
double amplitude = 1;
double NOISE_ENLARGEMENT = 0;
int main()
{
  double *ADC_output;
  ADC_output = (double *)malloc(sizeof(double) * OFDM_N);

  srand((unsigned)time(NULL)); // rand function

  for (Eb_N0 = 4; Eb_N0 < 40; Eb_N0 += 2)
  {
    double testMax = 0;
    CNR = (double)Eb_N0 + 3.0;
    for (int loop = 0; loop < LOOPN; loop++)
    {
      transmitter(transmitted_bit, modulated_signal);
      oversampling_GI(modulated_signal, transmitted_signal);
      awgn(transmitted_signal, transmitted_signal);
      removeGI(transmitted_signal, received_signal);
      ADC(received_signal, estimated_signal);
      //			for (int i = 0; i < OFDM_N; i++) {
      ////				SSE += pow((estimated_signal[i].real - received_signal[i].real), 2);
      //
      //				testMax = fabs(received_signal[i].real) > testMax ? fabs(received_signal[i].real) : testMax;
      //			}
      //			printf("testMax=%lf",testMax);
      FFT_demodulation(estimated_signal, received_bit);
      ber(loop, transmitted_bit, received_bit);
    }
    //		MSE = SSE / (OFDM_N* LOOPN);
    //		printf("MSE %10.8f\n", MSE);
  }
  return 0;
}
