/* freq_filter1.c  このプログラムの名前 */
#include<stdio.h>
#include<math.h>
#include"pgmlib2.h"
#include"fft.h"  /* FFT・IFFTの関数（付録C参照） */

/* 関数のプロトタイプ宣言 */
void make_original_data( int n );
void freq_filtering(void);
void make_output_image( int n );

int main(void)
{
    load_image( 0, "" );     /* 原画像 --> 画像No.0  */
    make_original_data( 0 ); /* 元のデータを作成する */
    FFT2( 1 );               /* ２次元 FFT の実行    */
    freq_filtering(0);       /* 周波数フィルタリング */
    //FFT2( -1 );              /* ２次元 逆FFT の実行  */
    make_output_image( 1 );  /* 画像No.1に画像を形成 */
    save_image( 1, "");      /* 画像No.1を出力する   */
    return 0;
}

void make_original_data( int n )
/* 画像No.nのデータを data[x][y], jdata[x][y] に代入する */
{
    int i,j;

    if ( width[n] != height[n] ){
        printf("縦と横の画素数が異なっています．\n");
        exit(1);
    } else {
        printf("\n読み込んだ画像を元データに直します．\n");
        num_of_data = width[n];
        for (j=0; j<num_of_data; j++)
            for (i=0; i<num_of_data; i++){
                 data[i][j] = (double)image[n][i][j];
                jdata[i][j] = 0.0;  /* 虚数部＝0 */
            }
    }
}

void freq_filtering(int n)
/* 周波数領域に対するフィルタリングを行う */
{
   
    int x, y,w,z;
    int p;
    double l;
    int len = width[n];
    int mod = len * 3 / 2;


    printf("\nフィルタリングを行います．\n");

    /* フィルタリングを行う．実際は何もしていない */

    for (x = 0; x < len; x++) {
        for (y = 0; y < len; y++) {
            w = ((x + len/2)% len) + len*3/2;
            z = ((y + len/2)% len) + len*3/2;
            data[w][z] = data[x][y];
            jdata[w][z] = jdata[x][y];
        }
    }
    //AB
    //CD
    //
    //   DC
    //   BA


    for (x = 0; x < len; x++) {
        for (y = 0; y < len; y++) {
          //  w = x+ mod;
         //   z = y+mod;
            p = data[x][y] * data[x][y] + jdata[x][y] * jdata[x][y];
        //    p = data[w][z] * data[w][z] + jdata[w][z] * jdata[w][z];
            l = sqrt(p);
            //if (l>800)
            //    printf("%d %d %lf %lf %lf\n", x, y, data[w][z], jdata[w][z], l);
            data[x][y] = l;
               
        }
    }

    
 
    //for (x = 0; x < len; x++) {
    //    for (y = 0; y < len; y++) {
    //       /* if (x>5&&x<510&& x==y)
    //            printf("%d %d :%d  %d\n", x, y, (int)data[x][y],(int)jdata[x][y]);*/        
    //        if(x==16&&y==16){
    //            data[x][y] = 0;
    //            jdata[x][y] = 0;
    //            data[512-x][512-y] = 0;
    //            jdata[512-x][512-y] = 0;
    //        }
    //    }
    //}
}

void make_output_image( int n )
/* データ data[y][x], jdata[y][x] を画像No.nに代入 */
{
    int x, y;

    printf("\n逆FFT変換後の画像を作成します．\n");
    width[n] = num_of_data;  height[n] = num_of_data;
    for(y=0; y<height[n]; y++)
        for(x=0; x<width[n]; x++){
            if ( data[x][y] < 0 ) data[x][y] = 0;
            if ( data[x][y] > MAX_BRIGHTNESS )
                data[x][y] = MAX_BRIGHTNESS;
            image[n][x][y] = (unsigned char)data[x][y];
        }
}
