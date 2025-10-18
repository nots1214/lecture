/* brightness.c  このプログラムの名前 */
#include<stdio.h>
#include"pgmlib2.h"

int trans_table[256];  /* 変換表（グラフ）*/

void trans( int n );
/* 画像No.nの画像を変換グラフで変換する */

int main(void)
{
    load_image( 0, "" );   /* ファイル → 画像No.0 */
    trans( 0 );            /* 画像No.0画像を濃度変換 */
    save_image( 0, "" );   /* 画像No.0 → ファイル */
    return 0;
}

void trans( int n )
/* 画像No.nの画像を変換グラフで変換する */
{
    int f;
    int x,y;
    int sft;  /* シフト量 */
    int suma = 0, sumb = 0, maxa = 0, mina = 255, maxb = 0,minb=255;
    double avea, aveb,cona,conb;

    do{
        printf("シフト量 [-128, 128] を入力して下さい：");
        scanf("%d",&sft);
    } while( sft<-128 || sft >128);    
    /* 変換表（グラフ）の設定 */
    for(f=0;f<256;f++){
        trans_table[f] = f + sft;
        if (trans_table[f] > 255) trans_table[f]=255;
        else if (trans_table[f] < 0) trans_table[f]=0;
    }
    /* 各画素の階調値を変換表に従って変換 */
    for(y=0;y<height[n];y++){
        for(x=0;x<width[n];x++){
            suma += image[n][x][y];
            if (image[n][x][y] > maxa)
                maxa = image[n][x][y];
            if (image[n][x][y] < mina)
                mina = image[n][x][y];
            image[n][x][y] = trans_table[ image[n][x][y] ];
            sumb += image[n][x][y];
            if (image[n][x][y] > maxb)
                maxb = image[n][x][y];
            if (image[n][x][y] < minb)
                minb = image[n][x][y];
        }
    }
    avea = (double)(suma )/ (double)(width[n] * height[n]);
    aveb = (double)(sumb )/(double) (width[n] * height[n]);
    cona = (double)((maxa - mina + 1)) / 256.0;
    conb = (double)((maxb - minb + 1)) / 256.0;
    printf("調整前　ブライトネス:%lf  コントラスト:%lf\n", avea, cona);
    printf("調整後　ブライトネス:%lf  コントラスト:%lf\n", aveb, conb);
}
