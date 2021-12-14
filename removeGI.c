#include "const.h"
#include "complex.h"

void removeGI(Complex (*signal), Complex(*output_signal))
{
	int j;
    for (j = 0; j < OFDM_N; j++)
    {
		output_signal[j].real = signal[j].real;
		output_signal[j].image = signal[j].image;
    }

}
