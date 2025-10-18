//2015.5.22
/*-----------------------*/
/* モード法によるニ値化 */
/*-----------------------*/
//
// 課題版
//
// ① ～ ⑦を埋めて，プログラムを完成させよ．
//

#include"stdio.h"
#include"pgmlib2.h"
#define level 3000 /* この水平線でヒストグラムをカットする．①の値は自分で決める */
/* 画像によって適切な値は変わるので注意． */
long int hist[256]; /* ヒストグラム用１次元配列 */
void make_histgram(int n);
void binarize2(int n);

int main(void)
{
	load_image(0, ""); /* ファイル → 画像No.0 */
	make_histgram(0); /* 画像No.0のヒストグラムの作成 */
	binarize2(0); /* 画像No.0を２値化（谷点検出）*/
	getchar();
	// save_image( 0, "" ); /* 画像No.0 → ファイル */
	save_image(0, ""); /* 画像No.0 → ファイル */
	return 0;
}

void binarize2(int n)
/* 画像No.n を２値化する（谷点検出） */
{
	int t1, t2, t;
	int i, j, x, y;

	/* ヒストグラムの平滑化（波形のノイズを除去するため） */
	for (i = 0; i < 3; i++) {
		for (j = 1; j < 255; j++) {
			hist[j] = (hist[j - 1] + hist[j] + hist[j + 1]) / 3;
		}
	}
	/* ヒストグラムの変更 */
	/* 一定数以下の階調は0，それ以外は1にする */
	for (i = 0; i < 256; i++) {
		if (hist[i] <= level) hist[i] = 0;
		else hist[i] = 1;
	}
	/* 谷点の検出 */
	i = 1; t1 = -1; t2 = -1; // t1,t2は図3.16(p.48)における記号
	do {
		if (hist[i - 1] == 1 && hist[i] == 0) { // t1の検出条件
			t1 = i;
		}
		else if (hist[i - 1] == 0 && hist[i] == 1 && t1 != -1) { // t2の検出条件
			t2 = i;
		}
		i++;
	} while (i < 256 && (t1 == -1 || t2 == -1)); // 終了条件
	printf("t1=%d, t2=%d\n", t1, t2);
	t = (t1 + t2) / 2; /* ２値化のしきい値 */
	/* 画像を２値化 */
	for (y = 0; y < height[n]; y++)
	{
		for (x = 0; x < width[n]; x++)
		{
			if (image[n][x][y] <= t) image[n][x][y] = 0;
			else image[n][x][y] = 255;
		}
	}

}

void make_histgram(int n)
/* 画像No.n を元にヒストグラムを作る */
{
	int i, x, y;

	/* ヒストグラムの初期化 */
	for (i = 0; i < 256; i++) hist[i] = 0;
	/* 画像をラスタスキャンしてグラフを作る */
	for (y = 0; y < height[n]; y++)
	{
		for (x = 0; x < width[n]; x++)
		{
			hist[image[n][x][y]]++; /* 累積を１増加 */
		}
	}
}