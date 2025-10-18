//
// J4情報工学実験4(3DCGモデリング)
// 課題1-7作成用プロジェクト
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include <windows.h>

#include "data.h"
#include "glut.h"


char *filename_prj = "../RadioTaisou.prj"; // この部分を自分の.prj名に書き換える
//char *filename_csv = "../test01.csv"; // この部分を自分の.csv名に書き換える
char* filename_csv = "../inaba_dai2(edit).csv"; // この部分を自分の.csv名に書き換える

// データ
bool t = false;
bool flag = true;
int frame_num = FRAME_NUM;
int num = 0;
int now_frame = 0;
XYZ markers[MARKER_NUM];
XYZ markers2[MARKER_NUM];
XYZ markersAll[FRAME_NUM][MARKER_NUM];
LINK links[LINK_NUM];
XYZ BaseAmount;
XYZ BaseAmount2;
XYZ ScaleAmount;
XYZ RotateAmount;
XYZ MoveAmount;
XYZ markers3[MARKER_NUM];
XYZ legAmount;
XYZ legAmount2;
XYZ line;
XYZ line2;
XYZ line3;
XYZ line4;

float trsMatrix[4][4];

int MouseState = 0;
int MousePushPos[2];
// 関数群---------------------

void initMatrix(float mat[][4])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
		}
	}
}
void scaleMatrix(float mat[][4], XYZ size)
{
	mat[0][0] *= size.x;
	mat[1][1] *= size.y;
	mat[2][2] *= size.z;
}
void combMatrix(float mat1[][4], float mat2[][4])
{
	float a[16];
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			a[4*j+i] = mat1[j][0] * mat2[0][i] + mat1[j][1] * mat2[1][i] + mat1[j][2] * mat2[2][i] + mat1[j][3] * mat2[3][i];
		}
	}
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			mat1[j][i] = a[4 * j + i];
		}
	}
}
void changeXYZbyMatrix(float mat[][4]) {
	for (int j = 0; j < MARKER_NUM; j++) {
			markers2[j].x = markers[j].x * mat[0][0] + markers[j].y * mat[1][0] + markers[j].z * mat[2][0] + mat[3][0];
			markers2[j].y = markers[j].x * mat[0][1] + markers[j].y * mat[1][1] + markers[j].z * mat[2][1] + mat[3][1];
			markers2[j].z = markers[j].x * mat[0][2] + markers[j].y * mat[1][2] + markers[j].z * mat[2][2] + mat[3][2];

	}
}

void changelineXYZbyMatrix(float mat[][4]) {
	for (int j = 0; j < MARKER_NUM; j++) {
		line2.x = line.x * mat[0][0] + line.y * mat[1][0] + line.z * mat[2][0];
		line2.y = line.x * mat[0][1] + line.y * mat[1][1] + line.z * mat[2][1];
		line2.z = line.x * mat[0][2] + line.y * mat[1][2] + line.z * mat[2][2];

	}
}
void changeline2XYZbyMatrix(float mat[][4]) {
	for (int j = 0; j < MARKER_NUM; j++) {
		line3.x = line.y * mat[0][0] + line.x * mat[1][0] + line.z * mat[2][0];
		line3.y = line.y * mat[0][1] + line.x * mat[1][1] + line.z * mat[2][1];
		line3.z = line.y * mat[0][2] + line.x * mat[1][2] + line.z * mat[2][2];

	}
}
void changeline3XYZbyMatrix(float mat[][4]) {
	for (int j = 0; j < MARKER_NUM; j++) {
		line4.x = line.z * mat[0][0] + line.y * mat[1][0] + line.x * mat[2][0];
		line4.y = line.z * mat[0][1] + line.y * mat[1][1] + line.x * mat[2][1];
		line4.z = line.z * mat[0][2] + line.y * mat[1][2] + line.x * mat[2][2];

	}
}
void generalchangeXYZbyMatrix(float mat[][4]) {
	for (int j = 0; j < MARKER_NUM; j++) {
		markers3[j].x = markers2[j].x * mat[0][0] + markers2[j].y * mat[1][0] + markers2[j].z * mat[2][0] + mat[3][0];
		markers3[j].y = markers2[j].x * mat[0][1] + markers2[j].y * mat[1][1] + markers2[j].z * mat[2][1] + mat[3][1];
		markers3[j].z = markers2[j].x * mat[0][2] + markers2[j].y * mat[1][2] + markers2[j].z * mat[2][2] + mat[3][2];
	}
}
void xrotateMatrix(float mat[][4], float value)
{
	value = value * PI / 180;
	mat[1][1] = cos(value);
	mat[2][2] = mat[1][1];
	mat[1][2] = sin(value);
	mat[2][1] = -mat[1][2];
}
void yrotateMatrix(float mat[][4], float value)
{
	value = value * PI / 180;
	mat[0][0] = cos(value);
	mat[2][2] = mat[0][0];
	mat[0][2] = -sin(value);
	mat[2][0] = -mat[0][2];
}

void zrotateMatrix(float mat[][4], float value)
{
	value = value * PI / 180;
	mat[0][0] = cos(value);
	mat[1][1] = mat[0][0];
	mat[0][1] = -sin(value);
	mat[1][0] = -mat[0][1];
}
void moveMatrix(float mat[][4], XYZ mv)
{
	mat[3][0] = mv.x;
	mat[3][1] = mv.y;
	mat[3][2] = mv.z;
}
void display()
{	// 描画
	for (int i = 0; i < MARKER_NUM; i++) {
		markers[i] = markersAll[now_frame][i];
	}
	float bufMatrix[4][4];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 画面をクリア
	glPointSize(8.0);

	initMatrix(trsMatrix);

	//genten
	initMatrix(bufMatrix);
	moveMatrix(bufMatrix,BaseAmount2 );
	combMatrix(trsMatrix, bufMatrix);
	//y
	initMatrix(bufMatrix);
	yrotateMatrix(bufMatrix, RotateAmount.y);
	combMatrix(trsMatrix, bufMatrix);
	//x
	initMatrix(bufMatrix);
	xrotateMatrix(bufMatrix, RotateAmount.x);
	combMatrix(trsMatrix, bufMatrix);
	//sc
	initMatrix(bufMatrix);
	scaleMatrix(bufMatrix,ScaleAmount);
	combMatrix(trsMatrix, bufMatrix);
	//changeXYZbyMatrix(trsMatrix);

	//gen
	initMatrix(bufMatrix);
	moveMatrix(bufMatrix,BaseAmount);
	combMatrix(trsMatrix, bufMatrix);

	initMatrix(bufMatrix);
	moveMatrix(bufMatrix, MoveAmount);
	combMatrix(trsMatrix, bufMatrix);

	changeXYZbyMatrix(trsMatrix);
	changelineXYZbyMatrix(trsMatrix);
	changeline2XYZbyMatrix(trsMatrix);
	changeline3XYZbyMatrix(trsMatrix);

	//影

	initMatrix(trsMatrix);

	initMatrix(bufMatrix);
	moveMatrix(bufMatrix, legAmount2);
	combMatrix(trsMatrix, bufMatrix);

	for (int i = 0; i < MARKER_NUM; i++)
	{
		markers3[i].x = markers[7].x;
	}

	initMatrix(bufMatrix);
	zrotateMatrix(bufMatrix, 90);
	combMatrix(trsMatrix, bufMatrix);



	initMatrix(bufMatrix);
	yrotateMatrix(bufMatrix, 210);
	combMatrix(trsMatrix, bufMatrix);
	

	initMatrix(bufMatrix);
	moveMatrix(bufMatrix, legAmount);
	combMatrix(trsMatrix, bufMatrix);
	generalchangeXYZbyMatrix(trsMatrix);
	for (int i = 0; i < MARKER_NUM; i++)
	{
		//markers3[i].y = -markers3[i].z*2 +markers[7].y;
		markers3[i].y = -markers3[i].z/2;
		//markers3[i].z = 0;
	}





	
	glPushMatrix();
	glTranslatef(0.0, 0.0, -1500.0);	// 見える場所へ移動

	//
	// スティック図の表示
	//
	
	// ----- マーカーを表示（赤点）		
	for (int i = 0; i < MARKER_NUM; i++)
	{
		glColor3f(1.0, 0.0, 0.0);
		if (i == 0) {
			glBegin(GL_LINE_LOOP);
			for (int k = -90; k < 90; k++) {
				for (int j = 0; j < 360; j++) {
					glVertex3f(markers2[i].x + R * cos(PI * j / 180) * cos(PI * k / 180), markers2[i].y + R * sin(j * PI / 180) * cos(PI * k / 180), markers2[i].z + R * sin(PI * k / 180));
					glVertex3f(markers2[i].x + R * cos(PI * (j + 1) / 180) * cos(PI * (k + 1) / 180), markers2[i].y + R * sin((j + 1) * PI / 180) * cos(PI * (k + 1) / 180), markers2[i].z * sin(PI * k  / 180));
				}
			}
		}
		else {
			glBegin(GL_POINTS);
			glVertex3f(markers2[i].x, markers2[i].y, markers2[i].z);
		}
		glEnd();
	}

	// ----- リンクラインを表示（緑線）
	for (int i = 0; i < LINK_NUM; i++)
	{
		glBegin(GL_LINES);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(markers2[links[i].s-1].x, markers2[links[i].s-1].y, markers2[links[i].s-1].z);
		glVertex3f(markers2[links[i].e-1].x, markers2[links[i].e-1].y, markers2[links[i].e-1].z);
		glEnd();
	}

	//--床の表示
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-200+BaseAmount.x, -200, 0);
	glVertex3f(-200 + BaseAmount.x, 200, -200);
	glVertex3f(200 + BaseAmount.x, 200,-200);
	glVertex3f(200 + BaseAmount.x, -200, 0);
	glEnd();

	//--影の表示

	glColor3f(0.3, 0.3, 0.3);
	for (int i = 0; i < MARKER_NUM; i++)
	{
		glBegin(GL_POINTS);
		glVertex3f(markers3[i].x, markers3[i].y, markers3[i].z);
		glEnd();
	}

	// ----- リンクラインを表示（影）
	for (int i = 0; i < LINK_NUM; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(markers3[links[i].s - 1].x, markers3[links[i].s - 1].y, markers3[links[i].s - 1].z);
		glVertex3f(markers3[links[i].e - 1].x, markers3[links[i].e - 1].y, markers3[links[i].e - 1].z);
		glEnd();
	}

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(line2.x+BaseAmount.x, line2.y , line2.z + BaseAmount.z);
	glVertex3f(-line2.x + BaseAmount.x, -line2.y , -line2.z + BaseAmount.z);
	glEnd();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(line3.x + BaseAmount.x, line3.y , line3.z + BaseAmount.z);
	glVertex3f(-line3.x + BaseAmount.x, -line3.y , -line3.z + BaseAmount.z);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(line4.x + BaseAmount.x, line4.y, line4.z + BaseAmount.z);
	glVertex3f(-line4.x + BaseAmount.x, -line4.y , -line4.z + BaseAmount.z);
	glEnd();
	

	//for (int i = 0; i < MARKER_NUM; i++)
	//{
	//	glBegin(GL_POINTS);
	//	glColor3f(1.0, 0.0, 0.0);
	//	glVertex3f(markers[i].x+150, markers[i].y, markers[i].z);
	//	glEnd();
	//}

	//// ----- リンクラインを表示（緑線）
	//for (int i = 0; i < LINK_NUM; i++)
	//{
	//	glBegin(GL_LINES);
	//	glColor3f(0.0, 1.0, 0.0);
	//	glVertex3f(markers[links[i].s - 1].x+150, markers[links[i].s - 1].y, markers[links[i].s - 1].z);
	//	glVertex3f(markers[links[i].e - 1].x+150, markers[links[i].e - 1].y, markers[links[i].e - 1].z);
	//	glEnd();
	//}
	
	//
	// スティック図の表示，終わり
	//

	if (t) {
		for (int i = 0; i < MARKER_NUM; i++) {
			printf("%lf,%lf,%lf\n", markers2[i].x, markers2[i].y, markers2[i].z);

		}
		printf("↑2倍------------------------------------------\n");
		t = false;
	}
	

	glPopMatrix();
	glutSwapBuffers();	// 画面入れ替え

}

void keyboard(unsigned char key, int x, int y)
{	// キーボードが押された
	switch (key) {
	case 'q':
		exit(0);	// 正常終了
	case 'u':
		ScaleAmount.x += 0.05;
		ScaleAmount.y += 0.05;
		num++;
		if (num == 20)
			t = true;
		break;
	case 'd':
		ScaleAmount.x -= 0.05;
		ScaleAmount.y -= 0.05;
		break;

	case 'z':
		for (int i = 0; i < MARKER_NUM; i++)
		{
			markers[i].z+=20;
		}
		break;
	case 'Z':
		for (int i = 0; i < MARKER_NUM; i++)
		{
			markers[i].z-=20;
		}
		break;
	case 'I':
		for (int i = 0; i < MARKER_NUM; i++)
		{
			markers2[i].x = markers[i].x;
			markers2[i].y = markers[i].y;
			markers2[i].z = markers[i].z;
		}
		ScaleAmount.x = 1.0;
		ScaleAmount.y = 1.0;
		ScaleAmount.z = 1.0;
		RotateAmount.x = 0;
		RotateAmount.y = 0;
		RotateAmount.z = 0;
		MoveAmount.x = 0;
		MoveAmount.y = 0;
		MoveAmount.z = 0;
		break;
	case 'Q':
		printf("x            y            z\n");
		for (int i = 0; i < MARKER_NUM; i++) {
			printf("%lf,%lf,%lf\n", markers2[i].x- BaseAmount.x, markers2[i].y- BaseAmount.y, markers2[i].z- BaseAmount.z);

		}
		//printf("↑平行移動orズーム後------------------------------------------\n");

		for (int i = 0; i < MARKER_NUM; i++) {
			printf("%lf,%lf,%lf\n", markers[i].x-BaseAmount.x, markers[i].y-BaseAmount.y, markers[i].z-BaseAmount.z);

		}
		//printf("↑元画像------------------------------------------\n");
		break;
	case 's':
		flag = !flag;
		break;

	}
	glutPostRedisplay();	// 再描画（disp関数を呼び出す）
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			MouseState = 1;
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			MouseState = 3;
		}
		MousePushPos[0] = x;
		MousePushPos[1] = y;
	}
	else if (state == GLUT_UP) {
		MouseState = 0;
	}
	glutPostRedisplay();
}

void my_motion(int x, int y)
{
	float dx = (float)(x - MousePushPos[0]);
	float dy = (float)(y - MousePushPos[1]);
	short n;

	if (MouseState == 1) {
		RotateAmount.x += dy;
		RotateAmount.y -= dx;
	}
	else if (MouseState == 2) {

	}
	else if (MouseState == 3) {
		MoveAmount.x += dx;
		MoveAmount.y += -dy;
	}
	MousePushPos[0] = x;
	MousePushPos[1] = y;
	glutPostRedisplay();
}

void my_reshape(int w, int h)
{

	glViewport(0.0, 0.0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, 1.0, 1000.0, 2000.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glutPostRedisplay();

}

void my_idle(void)
{
	glutPostRedisplay();
	if (flag) {
		now_frame++;
		if (now_frame == frame_num)
		{
			now_frame = 0;
		}
	}
	//Sleep(10);
}

int main(int argc, char **argv)
{	
	// メイン関数


	// ここでPRJファイルとCSVファイルを読み込む	
	read_prj_file(links, filename_prj);
	read_csv_file(markers, filename_csv);
	read_csv_file_all(markersAll,filename_csv);
	for (int i = 0; i < MARKER_NUM; i++) {
		markers2[i].x = markers[i].x;
		markers2[i].y = markers[i].y;
		markers2[i].z = markers[i].z;
	}
	initMatrix(trsMatrix);
	ScaleAmount.x = 1.0;
	ScaleAmount.y = 1.0;
	ScaleAmount.z = 1.0;
	RotateAmount.x = 0.0;
	RotateAmount.y = 0.0;
	RotateAmount.z = 0.0;
	MoveAmount.x = 0.0;
	MoveAmount.y = 0.0;
	MoveAmount.z = 0.0;
	double sum[3] = { 0 };
	for (int i = 0; i < MARKER_NUM; i++)
	{
		sum[0] += markers[i].x;
		sum[1] += markers[i].y;
		sum[2] += markers[i].z;
	}
	BaseAmount.x = sum[0] / MARKER_NUM;
	BaseAmount.y = sum[1] / MARKER_NUM;
	BaseAmount.z = sum[2] / MARKER_NUM;
	BaseAmount2.x = -BaseAmount.x;
	BaseAmount2.y = -BaseAmount.y;
	BaseAmount2.z = -BaseAmount.z;
	legAmount.x = markers[7].x;
	legAmount.y = markers[7].y;
	legAmount.z = markers[7].z;
	legAmount2.x = -legAmount.x;
	legAmount2.y = -legAmount.y;
	legAmount2.z = -legAmount.z;

	line.x = 100.0;
	line.y = 0.0;
	line.z = 0.0;

		printf("BaseAmount:%lf,%lf,%lf\n", BaseAmount.x, BaseAmount.y, BaseAmount.z);
		printf("BaseAmount2:%lf,%lf,%lf\n", BaseAmount2.x, BaseAmount2.y, BaseAmount2.z);
		printf("------------------------------------------\n");
		

		printf("x            y            z\n");
		for (int i = 0; i < 18; i++) {
			printf("%lf,%lf,%lf\n", markers[i].x, markers[i].y, markers[i].z);

		}
		printf("↑元画像------------------------------------------\n");
		/*for (int i = 0; i < 18; i++) {
			printf("%lf,%lf,%lf\n", markers2[i].x, markers2[i].y, markers2[i].z);

		}
		printf("------------------------------------------\n");*/




	glutInit(&argc, argv);           // glutを初期化
	glutInitWindowPosition(10, 10); // ウインドウ表示位置を指定
	glutInitWindowSize(300, 300);   // ウインドウの大きさを指定
	// ウインドウ内の描画モードを指定
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("3DCG Programming"); // ウインドウの名前
	glutDisplayFunc(display);             // 描画関数を設定
	glutIdleFunc(my_idle);
	glutKeyboardFunc(keyboard);           // キーボード関数を設定
	glutMouseFunc(mouse);
	glutMotionFunc(my_motion);
	glutReshapeFunc(my_reshape);


	
	

	// イベント（キーボード、マウスなどの入力）待ちループへ	
	// すべての命令は，glutMainLoop()の前に書く
	glutMainLoop();
	return 0;
}
