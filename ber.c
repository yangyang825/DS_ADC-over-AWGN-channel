
#include "const.h"

extern double CNR;

void ber(int loop, int(*tbit), int(*rbit))
{
  int n, error = 0;
  double Pe;
  static double AverageBER = 0.0;

  for (n = 0; n < BITN; n++)
  {
    if (tbit[n] != rbit[n])
    {
      error++;
    }
  }
  Pe = (double)error / (double)BITN;
  AverageBER += (double)Pe / LOOPN;
  if (loop % 10 == 0)
  {
    printf("loop=%d: Eb/N0 = %f, %e\t%e\n", loop, (CNR - 3.0), Pe, AverageBER);
  }

  if (loop == LOOPN - 1)
  {

    printf("LOOPN=%d,BER: Eb/N0 = %f, Average BER = %e\n", LOOPN, (CNR - 3.0), AverageBER);
    FILE *AWGNberADC = NULL;
    AWGNberADC = fopen("C:\\C-SIMULATIONRESULT\\0128AWGNberADC.csv", "a");
    fprintf(AWGNberADC, "0128-night: LOOPN=%d, Eb/N0=%f\t%e\n", LOOPN, (CNR - 3.0), AverageBER);
    fclose(AWGNberADC);

    AverageBER = 0.0;
  }
}
