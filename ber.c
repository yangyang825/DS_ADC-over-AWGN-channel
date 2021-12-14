
#include "const.h"

extern double CNR;


void ber(int loop, int(*tbit), int(*rbit)) {
    int n, error = 0;
    double Pe;
    static double AverageBER = 0.0;


    for (n = 0; n < BITN; n++) {
        if (tbit[n] != rbit[n])
        {
            error++;
        }
    }
    Pe = (double)error / (double)BITN;
    AverageBER += (double)Pe / LOOPN;
    if(loop%100 == 0){
    	printf("每次循环后的结果 # %5d: Eb/N0 = %f, %e\t%e\n", loop, (CNR - 3.0), Pe, AverageBER);
	}
    
    
    if (loop == LOOPN - 1) {
        FILE* file;
        printf("累加LOOPN=%d次结束之后的BER: Eb/N0 = %f, Average BER = %e\n", LOOPN, (CNR - 3.0), AverageBER);
        fopen_s(&file, "data2.txt", "a");
        fprintf(file, "LOOPN=%d, Eb/N0=%f\t%e\n", LOOPN, (CNR - 3.0), AverageBER);
    	fclose(file);

        AverageBER = 0.0;
    }

}
