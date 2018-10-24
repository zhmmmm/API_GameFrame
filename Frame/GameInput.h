#ifndef _GAME_INPUT_H_
#define _GAME_INPUT_H_

#include <windows.h>
#define _KS_CU 0 //��ǰ�ոյ���
#define _KS_KU 1 //һֱ���ǵ���״̬
#define _KS_CD 2 //�ոհ���
#define _KS_KD 3 //һֱ�ǰ��µ�״̬

class CGameInput
{
	friend void FrameInit();
	friend void FrameRun();
	friend void FrameEnd();

	//����
	HWND m_hWnd;

	//����״̬
	int m_KeyState[256];

	//����
	CGameInput(HWND hWnd);

	//���¼�״̬
	void Run();

public:

	//�õ�ָ������״̬
	int GetKeyState(unsigned char vk);

	//�õ��������ڿͻ��˵�λ��
	bool GetCursor(int* x, int* y);
};

#endif