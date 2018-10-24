#ifndef _GAME_INPUT_H_
#define _GAME_INPUT_H_

#include <windows.h>
#define _KS_CU 0 //当前刚刚弹起
#define _KS_KU 1 //一直就是弹起状态
#define _KS_CD 2 //刚刚按下
#define _KS_KD 3 //一直是按下的状态

class CGameInput
{
	friend void FrameInit();
	friend void FrameRun();
	friend void FrameEnd();

	//窗口
	HWND m_hWnd;

	//按键状态
	int m_KeyState[256];

	//构造
	CGameInput(HWND hWnd);

	//更新键状态
	void Run();

public:

	//得到指定键的状态
	int GetKeyState(unsigned char vk);

	//得到光标相对于客户端的位置
	bool GetCursor(int* x, int* y);
};

#endif