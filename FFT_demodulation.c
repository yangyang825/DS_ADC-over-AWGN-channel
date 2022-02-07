#include "const.h"
// extern Complex modulated_signal;
void clearHimpact(double(*estimated_signal));
void FFT(Complex(*estimated_signal), Complex(*recovered_signal));
void demodulation(Complex(*recovered_signal), int(*received_bit));

void FFT_demodulation(Complex(*estimated_signal), int(*received_bit))
{

  Complex *recovered_signal;
  recovered_signal = (Complex *)malloc(sizeof(Complex) * subcar_N);
  for (int i = 0; i < subcar_N; i++)
  {
    recovered_signal[i].real = 0;
    recovered_signal[i].image = 0;
  }
  FFT(estimated_signal, recovered_signal);
  /*
   * filter QPSK modulated signals: 	*recovered_signal: [0,349)=0, [349, 412]=QPSK_signals*, (412-512-612)=0, [612,675]=QPSK_signals, (675,1023]=0
   */
  Complex *QPSK_signal;
  QPSK_signal = (Complex *)malloc(sizeof(Complex) * POINT_N);
  for (int i = 0; i < POINT_N; i++)
  {
    QPSK_signal[i].real = recovered_signal[612 + i].real;
    QPSK_signal[i].image = recovered_signal[612 + i].image;
  }

  demodulation(QPSK_signal, received_bit);

  free(recovered_signal);
  free(QPSK_signal);
  recovered_signal = NULL;
}

void FFT(Complex(*IFFT_signal), Complex(*recovered_signal))
{
  Complex *temp_signal;
  temp_signal = (Complex *)malloc(sizeof(Complex) * OFDM_N);
  for (int i = 0; i < OFDM_N; i++)
  {
    temp_signal[i].real = 0;
    temp_signal[i].image = 0;
  }

  for (int n = 0; n < OFDM_N; n++)
  {
    for (int k = 0; k < OFDM_N; k++)
    {
      temp_signal[k].real = 1 / sqrt(OFDM_N) * ComplexMulti(IFFT_signal[k], Exp(-2 * PI * k * n / OFDM_N)).real;
      temp_signal[k].image = 1 / sqrt(OFDM_N) * ComplexMulti(IFFT_signal[k], Exp(-2 * PI * k * n / OFDM_N)).image;

      recovered_signal[n].real = recovered_signal[n].real + temp_signal[k].real;
      recovered_signal[n].image = recovered_signal[n].image + temp_signal[k].image;
    }
  }
}

void demodulation(Complex(*signal), int(*received_bit))
{

  int n;
  for (n = 0; n < POINT_N; n++)
  {
    if (signal[n].real > 0 && signal[n].image > 0)
    {
      received_bit[2 * n] = 0;
      received_bit[2 * n + 1] = 0;
    }
    else if (signal[n].real < 0 && signal[n].image > 0)
    {
      received_bit[2 * n] = 0;
      received_bit[2 * n + 1] = 1;
    }
    if (signal[n].real < 0 && signal[n].image < 0)
    {
      received_bit[2 * n] = 1;
      received_bit[2 * n + 1] = 1;
    }
    if (signal[n].real > 0 && signal[n].image < 0)
    {
      received_bit[2 * n] = 1;
      received_bit[2 * n + 1] = 0;
    }
  }
}
