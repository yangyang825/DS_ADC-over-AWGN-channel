#include "const.h"
#include "complex.h"

void channel(Complex (*transmitted_signal), Complex (*received_signal))
{
	double Complex fading_signal[SYMBOLN];
	fading(transmitted_signal, fading_signal);
	noise(fading_signal, received_signal);
}

void fading(Complex (*transmitted_signal), Complex(*fading_signal))
{
	
}

void noise(Complex *(fading_signal), Complex (*received_signal))
{
	
}




