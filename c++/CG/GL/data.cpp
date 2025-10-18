#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

//
// ファイル読み込み関数のサポート用なので，目を通さなくても良い
//
char* strtok_csv(char *value)
{
	static char strbuf[STR_SIZE];	// 元データ
	static int	spos, epos; 	// 指している位置
	char p[256] = "0.0";	// 戻り値
	int	i, cnt = 0;

	if (value != NULL) {	// データをコピー
		for (i = 0; value[i] != '\0'; i++) {
			strbuf[i] = value[i];
		}
		strbuf[i] = '\0';
		spos = 0;	epos = 0;	// 指している位置を初期化
	}

	while (1) {
		if (strbuf[epos] == ',') {	// ,を発見
			if (spos == epos) {	// 連続して,が進んだ場合
				epos++;
				spos = epos;
				return NULL;
			}
			else {
				break;
			}
		}
		else if (strbuf[epos] == '\0') {	// 終端記号を発見
			break;
		}
		else {	// それ以外
			epos++;
		}
	}
	cnt = 0;
	for (i = spos; i < epos; i++) {
		p[cnt] = strbuf[i];
		cnt++;
	}
	p[cnt] = '\0';


	epos++;
	spos = epos;
	return p;

}

//
// プロジェクトファイルを読み込むためのプログラム
//
void read_prj_file(LINK *l, char *fn)
{ // PRJファイルからデータの読み込み

	FILE *fp;
	char str[STR_SIZE], *tp, *tp2;
	int  i;

	if ((fp = fopen(fn, "r")) == NULL) {
		printf(" ファイル[%s]が開きません。\n", fn);
		exit(1);
	}
	printf(" <%s>のファイルを開きました。\n", fn);
	// リンク情報を探す
	while (fgets(str, STR_SIZE, fp) != NULL) {
		if (strcmp(str, "[Linkages]\n") == 0) {
			break;
		}
	}
	fgets(str, STR_SIZE, fp);	// Comment行は飛ばす
	fgets(str, STR_SIZE, fp);	// NumberOf行は飛ばす

	// リンク情報を配列に格納
	for (i = 0; i < LINK_NUM; i++) {
		fgets(str, STR_SIZE, fp);
		tp = strtok(str, ",");
		tp = strtok(NULL, ",");
		tp = strtok(NULL, ",");
		tp = strtok(NULL, ",");
		tp2 = strtok(tp, " ");
		l[i].s = atoi(tp2); // リンクの始点を表わすマーカ番号
		tp2 = strtok(NULL, "\0");
		l[i].e = atoi(tp2); // リンクの終点を表わすマーカ番号

	}
	fclose(fp);
}

void read_csv_file(XYZ *m, char *fn)
{ // CSVファイルからデータの読み込み

	FILE *fp;
	char str[STR_SIZE], *tp;
	int  i;

	if ((fp = fopen(fn, "r")) == NULL) {
		printf(" ファイル[%s]が開きません。\n", fn);
		exit(1);
	}
	printf(" <%s>のファイルを開きました。\n", fn);
	fgets(str, STR_SIZE, fp); // 1行目は省く（カラム名のため）
	fgets(str, STR_SIZE, fp); // 2行目を取得

	tp = strtok_csv(str);  // フレーム番号取得

	tp = strtok_csv(NULL); // 時間取得
	for (i = 0; i < MARKER_NUM; i++) {	// データ取得
		tp = strtok_csv(NULL);     // x値取得

		if (tp != NULL) {
			m[i].x = (float)atof(tp); // x値を配列に格納
		}
		else {
			m[i].x = NO_DATA;  // x値にNO_DATAを格納
		}

		tp = strtok_csv(NULL);     // y値取得
		if (tp != NULL) {
			m[i].z = (float)atof(tp); // y値を配列に格納
		}
		else {
			m[i].z = NO_DATA;  // x値にNO_DATAを格納
		}

		tp = strtok_csv(NULL);     // z値取得
		if (tp != NULL) {
			m[i].y = (float)atof(tp); // z値を配列に格納
		}
		else {
			m[i].y = NO_DATA;  // x値にNO_DATAを格納
		}
	}
	fclose(fp);
}

void read_csv_file_all(XYZ m[][MARKER_NUM], char *fn)
{ // CSVファイルからデータの読み込み

	FILE *fp;
	char str[STR_SIZE], *tp;

	int  i, f;

	if ((fp = fopen(fn, "r")) == NULL) {
		printf(" ファイル[%s]が開きません。\n", fn);
		exit(1);
	}
	printf(" <%s>のファイルを開きました。\n", fn);
	fgets(str, STR_SIZE, fp); // 1行目は省く（カラム名のため）

	for (f = 0; f < FRAME_NUM; f++) {
		fgets(str, STR_SIZE, fp); // 2行目以降を取得

		tp = strtok_csv(str);  // フレーム番号取得
		tp = strtok_csv(NULL); // 時間取得
		for (i = 0; i < MARKER_NUM; i++) {	// データ取得
			tp = strtok_csv(NULL);     // x値取得
			if (tp != NULL) {
				m[f][i].x = (float)atof(tp); // x値を配列に格納
			}
			else {
				m[f][i].x = NO_DATA;  // x値にNO_DATAを格納
			}
			tp = strtok_csv(NULL);     // y値取得
			if (tp != NULL) {
				m[f][i].z = (float)atof(tp); // y値を配列に格納
			}
			else {
				m[f][i].z = NO_DATA;  // x値にNO_DATAを格納
			}
			tp = strtok_csv(NULL);     // z値取得
			if (tp != NULL) {
				m[f][i].y = (float)atof(tp); // z値を配列に格納
			}
			else {
				m[f][i].y = NO_DATA;  // x値にNO_DATAを格納
			}
		}
	}
	fclose(fp);
}