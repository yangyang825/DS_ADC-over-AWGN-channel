#include "const.h"
#include "complex.h"

extern double CNR, NOISE_ENLARGEMENT;

void noise_generator(Complex(*noise));
double uniform01();

void awgn(Complex(*input_signal), Complex(*output_signal))
{
  Complex noise[OFDM_N];
  noise_generator(noise);

  for (int i = 0; i < OFDM_N; i++)
  {
    output_signal[i] = ComplexAdd(input_signal[i], noise[i]);
  }
}

void noise_generator(Complex(*noise))
{
  int n;
  double u1, u2, num;

  num = pow(10.0, (-CNR / 10));
  //	num = num * NOISE_ENLARGEMENT; //NOISE_ENLARGEMENT is determined by: (power of transmitted signals)/(power of modulated signals)
  for (n = 0; n < OFDM_N; n++)
  {

    u1 = uniform01();
    u2 = uniform01();

    noise[n].real = sqrt(-num * log(u1)) * cos(2.0 * PI * u2);
    noise[n].image = sqrt(-num * log(u1)) * sin(2.0 * PI * u2);
  }
}

double uniform01()
{
  double u;
  u = (double)rand() / RAND_MAX;
  while (u == 0.0)
  {
    u = (double)rand() / RAND_MAX;
  }
  return u;
}
