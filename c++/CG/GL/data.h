#ifndef _DATA_H_
#define _DATA_H_

#define PI		3.141592

#define R 10

#define STR_SIZE   2048
#define NO_DATA    1000000.0

#define	MARKER_NUM 16 // マーカ数はこちらに記述し，この名前で呼び出す
#define LINK_NUM   21 // リンク数はこちらに記述し，この名前で呼び出す
#define FRAME_NUM  11337 // フレーム数はこちらに記述し，この名前で呼び出す

// 頂点（x,y,z）用構造体
typedef struct XYZ{
	float x, y, z; // x,y,zには，マーカ位置のそれぞれの軸における座標が格納される
} XYZ;
// リンク用構造体
typedef struct LINK{
	// ■注意■: マーカ番号は1から振られる
	int s, e; // sとeには，リンクの両端のマーカ番号が格納される
} LINK;

extern char* strtok_csv(char *);
extern void read_csv_file( XYZ *, char * );
extern void read_prj_file( LINK *, char * );
extern void read_csv_file_all( XYZ m[][MARKER_NUM], char * );

#endif
