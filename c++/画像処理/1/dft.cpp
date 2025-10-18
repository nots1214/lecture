#include "stdio.h"
#include "math.h"
#include "fft.h"
#define DATA_SIZE 16 //データサイズ
#define PI 3.141592653589
int main() {
	int i, x;
	double fi[DATA_SIZE] = { 0 }; // 虚部は常にゼロ
	double fr[DATA_SIZE]; // 実部
	double Fi[DATA_SIZE];
	double Fr[DATA_SIZE];
	for (x = 0; x < DATA_SIZE; x++) {
		//fr[x] = 1.0;	//ｆｒ[ ]に条件(1)から(6)のパターンに応じて設定する
		//fr[x] = cos(PI / 8 * x);
		//fr[x] = sin(PI / 2 * x);
		fr[x] = cos(PI / 4 * x);
		//fr[x] = cos(PI / 2 * x);
		//fr[x] = cos(PI / 8 * x) + cos(PI / 2 * x);
	}

	FFT1(fr, fi, DATA_SIZE, 1); // FFTの実行
	for (int i = 0; i < 16; i++)
	{
		Fi[i] = fi[i];
		Fr[i] = fr[i];
	}
	for (int i = 0; i < 16; i++)
	{
		fr[i] = Fr[(i + 8) % 16];
		fi[i] = Fi[(i + 8) % 16];
	}
	FFT1(fr, fi, DATA_SIZE, -1); // FFTの実行
	for (x = 0; x < DATA_SIZE; x++)
	{
		printf("f(%d)=%lf+i%lf\n", x, fr[x], fi[x]);
	}
	return 0;
}