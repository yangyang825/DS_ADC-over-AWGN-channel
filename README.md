# DS_TDC-over-AWGN-channel
RZ TDC, ADC, oversampling


## 1. Delta-Sigma ADC simulations
### 1.1 oversampling parameters
```c
//set IF frequency
#define N_C                Left_StartF-POINT_N/2
#define Left_StartF                subcar_N/2-deltaFrequency
#define Right_StartF        subcar_N/2+deltaFrequency
#define deltaFrequency        100
```
Unlike RZ TDC, the DS ADC needs both imaginary parts and real parts of bandpass signals to recover baseband signals. In order to simplify the receiver, conjugate modulated signals were used to set the imaginary part of bandpass signals to zero.
>>《Digital Communications, 5-th Edition》, page 19-20, Hermitian symmetry

For real bandpass signal s_IF(t), the magnitude of subcarrier S(i) is even and its phase is odd.
### 1.2 noise enlargement
We obtained a real bandpass signal in the transmitter, however we should consider the image part. Because if we ignore the image part and set it as zero, it the same as we mutually ignore the effects of AWGN over the image part.
In this case, BER will be smaller than the theory.

Solution: set NOISE_ENLARGEMENT=1, and consider the image part of bandpass signals.

### 1.3 amplitude
$$
amplitude=VREF
$$

This is the reference voltage of DS ADC, its value affects the simulation results a lot. It should satisfy

$$
amplitude = | VREF |>Math.max(received_signal[i].real)
$$
