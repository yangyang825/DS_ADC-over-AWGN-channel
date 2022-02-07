#include "const.h"
#include "complex.h"
void bit_generator(int(*bit));
void QPSK_modulator(int *(bit), Complex(*signal));

void transmitter(int(*bit), Complex(*signal))
{
  bit_generator(bit);
  QPSK_modulator(bit, signal);
}

void bit_generator(int(*bit))
{
  int n;
  for (n = 0; n < BITN; n++)
  {
    bit[n] = rand() & 0x1;
  }
}

void QPSK_modulator(int *(bit), Complex(*signal))
{
  int n, bit1, bit2, symbol;
  int bin2sym[2][2] = {
      {0, 1},
      {3, 2}};
  double sym2sgnl[4][2] = {
      {OneBySqrt2, OneBySqrt2},
      {-OneBySqrt2, OneBySqrt2},
      {-OneBySqrt2, -OneBySqrt2},
      {OneBySqrt2, -OneBySqrt2}};

  for (n = 0; n < POINT_N; n++)
  {
    bit1 = bit[n * 2];
    bit2 = bit[n * 2 + 1];
    symbol = bin2sym[bit1][bit2];
    signal[n].real = sym2sgnl[symbol][0];
    signal[n].image = sym2sgnl[symbol][1];
  }
}
