#include "../Frame/Frame.h"
#include "Render2DPip.h"
#include <ctime>
using namespace std;

//�������ô���(�ͻ���)��С��FPS��������������Ժ����ȵ��õĺ���
//�������ִֻ��һ��
void GameSetClientAndFPS(int* cw, int* ch, int* fs)
{
	*cw = 800;
	*ch = 600;
	*fs = 60;
}

int fontid = -1;
float angle = 0.0f;
CModel2D mod;
int posx = 400, posy = 300;//�������λ��
int Red_X = 0;//posx / 2.0f
int Red_Y = 0;//posy / 2.0f
int dirs[2][4] = {
	0,0,-1,1,
	-1,1,0,0
};
float speed = 5.0f;

void GameInit()
{
	srand(GetTickCount());
	fontid = g_GameOutput->LoadFont(30, 50, "����");
	bool ret = mod.LoadModelFromFile("Tank.txt");
	if (ret) {}
	else { return; }
}

//��Frame���ѭ������
void GameRun()
{
	CMatrix3 wm;//����任����
	CMatrix3 pm;//ͶӰ����
	CMatrix3 vm;//�ӿھ���

	wm.Scale(20, 20).Translate(posx, posy);
	SetMatrix(MATRIX_WORLD, &wm);

	CreateProjectMatrix(posx - 250, posx + 250, posy - 250, posy + 250, &pm);
	SetMatrix(MATRIX_PROJECT, &pm);

	CreateViewportMatrix(Red_X, Red_Y, 400, 300, &vm);
	SetMatrix(MATRIX_VIEW, &vm);
	//�����ӿ����
	g_GameOutput->DrawRectangle(200, 150, 600, 450, RGB(0, 0, 0), RGB(255, 255, 255));

	DrawModel(&mod, RGB(255, 0, 0));
	SetMatrix(MATRIX_WORLD, &wm);

	if (g_GameInput->GetKeyState(VK_UP) == _KS_KD)
	{
		Red_X += dirs[0][0] * speed;
		Red_Y += dirs[1][0] * speed;

	}
	if (g_GameInput->GetKeyState(VK_DOWN) == _KS_KD)
	{
		Red_X += dirs[0][1] * speed;
		Red_Y += dirs[1][1] * speed;
	}
	if (g_GameInput->GetKeyState(VK_LEFT) == _KS_KD)
	{
		Red_X += dirs[0][2] * speed;
		Red_Y += dirs[1][2] * speed;
	}
	if (g_GameInput->GetKeyState(VK_RIGHT) == _KS_KD)
	{
		Red_X += dirs[0][3] * speed;
		Red_Y += dirs[1][3] * speed;
	}
}

//Ҫ��������init�����м��ص�ͼƬ�������ͷŵ���
//������������˳�����Ϸѭ������õ�һ�Ρ�
void GameEnd()
{
	g_GameOutput->ReleaseFont(fontid);
}