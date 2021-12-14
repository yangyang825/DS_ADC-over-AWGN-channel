#include "const.h"
#include "complex.h"
double estimate(double *realSignal);
// extern MSE, SSE;

void ADC(Complex(*received_signal), double(*estimated_signal))
{

  for (int i = 0; i < OFDM_N; i++)
  {
    estimated_signal[i] = estimate(&received_signal[i].real);
    // printf("i=%d, estimated_signal = %lf   received_signal=%lf \n", i, estimated_signal[i], received_signal[i].real);
  }
}

double estimate(double *realSignal)
{
  double estimated_signal = 0;

  int adcN = 35; //ȡ������.......����д��const.h���Ƶ��1/fs��ʾ

  double delta;
  double sumOfDelta = 0;
  int bitStream[35];
  // int *bitStream;
  // bitStream = (int*)malloc(sizeof(int) * adcN);
  for (int j = 0; j < adcN; j++)
  {
    //��ʼ��
    bitStream[j] = 0;
  }

  double DACoutput = Vref; //+ or -Vref

  //����ÿһ���źŶ�ȡadcN��ƽ��ֵ
  for (int j = 0; j < adcN; j++)
  {
    //��ʼ��
    bitStream[j] = 0;
    delta = *realSignal - DACoutput;
    sumOfDelta += delta;
    // printf("delta = %f\n", delta);
    // printf("sumOfDelta = %lf\n", sumOfDelta);

    if (sumOfDelta >= 0)
    {
      bitStream[j] = 1;
      DACoutput = Vref;
    }
    else
    {
      bitStream[j] = 0;
      DACoutput = -Vref;
    }
    // printf("%d\n", bitStream[j]);
    // printf("DACoutput_signal = %lf\n", DACoutput);
    estimated_signal += DACoutput;
    // free(bitStream);
    *bitStream = NULL;
  }
  //��ƽ��
  estimated_signal /= adcN;
  //����ѭ����������,�����һ��������transmitted_signal[0]��ֵ
  return estimated_signal;
}
