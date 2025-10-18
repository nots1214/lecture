// 2013.6.6
/********************************/
/* ｐ－タイル法による二値化処理 */
/********************************/


/* binarization.c このプログラムの名前 */
#include"stdio.h"
#include"pgmlib2.h"
void binarize_ptile(int n);
void histogram(int n, int hst[]);
int search_thvalue(int n, double pval, int hst[]);

int hst[256]; // ヒストグラム格納用

int main(void)
{
	load_image(0, ""); /* ファイル → 画像No.0 */
	binarize_ptile(0); /* 画像No.0を２値化 */
	save_image(0, ""); /* 画像No.0 → ファイル */
	getchar();
	getchar();
	return 0;
}


/*-------------*/
/* 二値化処理　*/
/*-------------*/

void binarize_ptile(int n)
/* 画像No.n を２値化する */
{
	int thvalue; /* ２値化のしきい値 */
	int x, y;
	double pval; //p値


	printf("p値(%%)=");
	scanf("%lf", &pval);

	/*--- 画像のヒストグラムの算出 ---*/
	histogram(n, hst);


	/*--- しきい値の探索---*/
	thvalue = search_thvalue(n, pval, hst);
	printf("しきい値=%d\n", thvalue);

	/*--- 画像を２値化 ---*/
	for (y = 0; y < height[n]; y++) {

		for (x = 0; x < width[n]; x++)
		{
			if (image[n][x][y] <= thvalue) image[n][x][y] = 0;
			else image[n][x][y] = 255;
		}
	}
}


/*--------------------*/
/* ヒストグラムの算出 */
/*--------------------*/

void histogram(
	int n, // 画像番号
	int hst[] // ヒストグラム格納用
)
{
	int x, y;

	/*--- hst[]のクリア ---*/
	for (x = 0; x < 256; x++) {
		hst[x] = 0;
	}

	for (y = 0; y < height[n]; y++)
	{
		for (x = 0; x < width[n]; x++)
		{
			hst[image[n][x][y]]++;
		}
	}
}


/*----------------*/
/* しきい値の探索 */
/*-----------------*/
//
// 戻り値がしきい値
//
int search_thvalue(
	int n, // 画像番号
	double pval,// p値(%)
	int hst[] // ヒストグラム
)
{
	/*-----

	この部分を記述する(ヒストグラムからしきい値を求める）

	----*/
	int x;
	int value = 0;
	int p, q;
	int sum = 0;
	/*for (x = 0; x < 256; x++) {
		value += hst[x];
	}*/
	value = height[n] * width[n];
	p = value *(1- pval);
	for (x = 0; x < 256; x++) {
		sum += hst[x];
		if (sum >= p)
			break;
	}
	q = x;
	return x;// しきい値
}