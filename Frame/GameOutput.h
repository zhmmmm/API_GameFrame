#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_

#include <windows.h>
#include <vector>

//��Ϸ����HDC
extern HDC g_GameHDC;

class CGameOutput
{
	friend void FrameInit();
	friend void FrameRun();
	friend void FrameEnd();

	HWND m_hWnd;
	int m_ClientPW;
	int m_ClientPH;
	HDC m_MainDC;
	HDC m_BackDC;
	std::vector<HFONT> m_Fonts;
	std::vector<HDC> m_Images;

	//����
	CGameOutput(HWND hWnd);

	//����
	~CGameOutput();

	//0�����λ���
	void BeginOutput();
	void EndOutput();

public:

	//����ĺ����У�ֻ��LoadFont��LoadBmp�Ƿ���
	//��Ϸ��ʼ��������ʹ�ã��������к�������Ӧ��
	//������Ϸѭ����ʹ�õ�

	//1��ͼԪ

	//�����߶�
	void DrawLine(
		int x1, //�˵�1��x����
		int y1, //�˵�1��y����
		int x2, //�˵�2��x����
		int y2, //�˵�2��y����
		int color); //��ɫ

	//���ƾ���
	void DrawRectangle(
		int x1, //���Ͻ�x����
		int y1, //���Ͻ�y����
		int x2, //���½�x����
		int y2, //���½�y����
		int color1, //�����ɫ
		int color2); //�����ɫ

	//����Բ��
	void DrawEllipse(
		int x1, //���Ͻ�x����
		int y1, //���Ͻ�y����
		int x2, //���½�x����
		int y2, //���½�y����
		int color1, //�����ɫ
		int color2); //�����ɫ

	//��Ϊ���ֶ��ԣ����ÿ�ζ��Ǵ��������ơ����ٵĻ�����
	//�Ŀ����ǱȽϴ�ģ�����������Ȼ�ˢ������ռ�ø�����
	//�����Դ�����Բ�ȡ���ء�ʹ�á����ٵķ�ʽ�����й���
	//��ͬ��λͼҲӦ��������ע�����Ӧ���ڳ�ʼ���׶Ρ�ʹ
	//�þ�������Ϸѭ���׶Ρ�����������Ϸ�����׶������

	//2������

	//�������ַ��ش���������ֵ�����id
	int LoadFont(
		int w, //�����
		int h, //�����
		const char* f); //�������

	//ж������
	bool ReleaseFont(int index);

	//���Ƶ�������
	void DrawString1(
		int index,
		int x,
		int y,
		const char* t,
		int color);

	//���ƶ�������
	void DrawString2(
		int index,
		int x1,
		int y1,
		int x2,
		int y2,
		const char* t,
		int color);

	//3��ͼ��

	//����λͼ
	int LoadBmp(const char* fn);

	//ж��λͼ
	bool ReleaseBmp(int index);

	//����λͼ1
	bool DrawBmp1(
		int index,//LoadBmp���ص�ͼƬID
		int dx, int dy, int dw, int dh,//Ҫ���Ƶ�������ʲô��������
		int sx, int sy);//��ԴͼƬ��Ҫ����ͼƬ�������Ͻ�����

	//����λͼ2
	bool DrawBmp2(
		int index,//LoadBmp���ص�ͼƬID
		int dx, int dy, int dw, int dh,//Ҫ���Ƶ�������ʲô��������
		int sx, int sy, int sw, int sh,//��ԴͼƬ��Ҫ����ͼƬ��������
		int tc);//����ʱҪ���Ե�����ɫ

	//�õ��ͻ�����
	int GetClientPW();

	//�õ��ͻ�����
	int GetClientPH();

	HDC GetBackHDC();
};

#endif