#include "const.h"
#include "complex.h"
double estimate(double *realSignal);
extern double amplitude;
void ADC(Complex(*received_signal), Complex(*estimated_signal))
{

  for (int i = 0; i < OFDM_N; i++)
  {
    estimated_signal[i].real = estimate(&received_signal[i].real);
    //		estimated_signal[i].image = 0;//leave noise in image part or not
    estimated_signal[i].image = received_signal[i].image; // remain the noise over image part, incase BER is smaller than the theory
  }
}

double estimate(double *realSignal)
{
  double estimated_signal = 0;

  int adcN = SAMPLING_RATE_ADC;

  double delta;
  double sumOfDelta = 0;
  int bitStream[SAMPLING_RATE_ADC];
  // int *bitStream;
  // bitStream = (int*)malloc(sizeof(int) * adcN);
  for (int j = 0; j < adcN; j++)
  {
    bitStream[j] = 0;
  }

  double DACoutput = amplitude; //+ or -Vref
  for (int j = 0; j < SAMPLING_RATE_ADC; j++)
  {
    bitStream[j] = 0;
    delta = *realSignal - DACoutput;
    sumOfDelta += delta;

    if (sumOfDelta >= 0)
    {
      bitStream[j] = 1;
      DACoutput = amplitude;
    }
    else
    {
      bitStream[j] = 0;
      DACoutput = -amplitude;
    }
    estimated_signal += DACoutput;
  }
  estimated_signal /= SAMPLING_RATE_ADC;
  return estimated_signal;
}
