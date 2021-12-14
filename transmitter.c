#include "const.h"
#include "complex.h"
void bit_generator(int (*bit));
void QPSK_modulator(int *(bit), Complex (*signal));

void transmitter(int (*bit), Complex (*signal))
{
	bit_generator(bit);
	QPSK_modulator(bit, signal);
}

void bit_generator(int (*bit))
{
	int n;
	for(n=0; n<BITN; n++){
    	bit[n] = rand() & 0x1;
	}
}

void QPSK_modulator(int *(bit), Complex (*signal))
{
	int n, bit1, bit2, symbol;
	//状态索引数组
	int bin2sym[2][2] = {
		{ 0, 1},
		{ 3, 2}
	};

	//状态数组
	double sym2sgnl[4][2] = {
		{ OneBySqrt2, OneBySqrt2},
		{-OneBySqrt2, OneBySqrt2},
		{-OneBySqrt2,-OneBySqrt2},
		{ OneBySqrt2,-OneBySqrt2}
	};


	for(n=0; n<POINT_N; n++){
        //获取信号随机状态，从生成的bit[128]数组中取连续的两位
		bit1 = bit[n*2];
		bit2 = bit[n*2+1];
		//bit1，bit2取值都是从0,1中任取一个
		symbol = bin2sym[bit1][bit2];
		//更新信号量。symbol的取值是0,1,2,3四个数字中随机任一个。将对应symbol值映射到信号数组中
		signal[n].real = sym2sgnl[symbol][0];
		signal[n].image = sym2sgnl[symbol][1];
        //得到数组signal[64][2]，每一行代表ABCD四个点中任一个
	}
}
