/* shape_recog1.c  このプログラムの名前 */
#include<stdio.h>
#include"pgmlib2.h"
#include"labeling.h"  /* label[][], labeling()を含む */
void recognition( int n1, int n2 );

int main(void)
{
    printf("２値画像（白：255，黒：0）を読み込みます\n");
    load_image( 0, "" );   /* ファイル → 画像No.0(原画像)   */
    recognition( 0, 1 );   /* 画像No.0の認識結果を画像No.1へ */
    save_image( 1, "" );   /* 画像No.1 → ファイル */
    return 0;
}

void recognition( int n1, int n2 )
/* 画像No.n1を認識した結果の画像をNo.n2に作る */
{
    int i,num,x,y,h[50],w[50];
    int area[50],xmin,ymin,xmax,ymax,MINAREA;
    int max;
    int class[50];
    double size[50], inpro[20][20] = { 0 };
    double ratio,MINRATIO;

    /* 画像No.n2 の準備 */  copy_image(n1,n2);
    /* ラベリング(labeling.hの関数labering()を利用) */
    num = labeling( n1 );
    printf("画像中の図形領域数＝%d\n",num);
    /*printf("面積のしきい値(例:1000)：");
    scanf("%d",&MINAREA);
    printf("外接四角形充填率のしきい値(例:0.5)：");
    scanf("%lf",&MINRATIO);*/
    /* 面積・外接四角形充填率で分類 */
    for(i=1;i<=num;i++){
        area[i]=0;
        xmin=width[n1];   xmax=0;
        ymin=height[n1];  ymax=0;
        for(y=0;y<height[n1];y++)
            for(x=0;x<width[n1];x++)
                if (label[x][y] == i){
                    area[i]++;
                    if (x < xmin) xmin=x;  if (x > xmax) xmax=x;
                    if (y < ymin) ymin=y;  if (y > ymax) ymax=y;
                }
        w[i] = xmax - xmin;  if ( w == 0 ) w[i]=1;
        h[i] = ymax - ymin;  if ( h == 0 ) h[i]=1;
        ratio = (double)area[i]/w[i]/h[i];

    }
  
  
        for (i = 1; i <= num; i++) {
            if (w[i] < 60 && area[i] < 1550)
                class[i] = 1;
            else if (w[i] >= 60 &&h[i]>100&&area[i] > 2000)
                class[i] = 3;
            else
                class[i] = 2;
        }
 

    for(i=1;i<=num;i++){
        for (y = 0; y < height[n1]; y++)
            for (x = 0; x < width[n1]; x++)
                if (label[x][y] == i) {
                    image[n2][x][y] = class[i]*75;

                }
        printf("ラベル番号%d:面積%d:水平方向最大幅%d:垂直方向最大幅%d\n", i, area[i], w[i], h[i]);
    }
    
}
