#include "GameInput.h"

CGameInput::CGameInput(HWND hWnd)
:
m_hWnd(hWnd)
{
	for (int i = 0; i < 256; ++i)
		m_KeyState[i] = _KS_CU;
}

void CGameInput::Run()
{
	for (int i = 0; i < 256; ++i)
	{
		//当前按下
		if (GetAsyncKeyState(i) & 0x8000)
		{
			//如果刚才为放开
			if (_KS_CU == m_KeyState[i] || _KS_KU == m_KeyState[i])
				m_KeyState[i] = _KS_CD;
			//如果刚才为按下
			else
				m_KeyState[i] = _KS_KD;
		}
		//当前放开
		else
		{
			//如果刚才为放开
			if (_KS_CU == m_KeyState[i] || _KS_KU == m_KeyState[i])
				m_KeyState[i] = _KS_KU;
			//如果刚才为按下
			else
				m_KeyState[i] = _KS_CU;
		}
	}
}

int CGameInput::GetKeyState(unsigned char vk)
{
	return m_KeyState[vk];
}

bool CGameInput::GetCursor(int* x, int* y)
{
	//得到光标在桌面的坐标
	POINT p;
	GetCursorPos(&p);

	//光标的桌面坐标转换为窗口的客户区坐标
	ScreenToClient(m_hWnd, &p);

	//设置结果
	*x = p.x;
	*y = p.y;

	//得到窗口的客户区矩形
	RECT r;
	GetClientRect(m_hWnd, &r);
	return p.x >= r.left && p.x < r.right && p.y >= r.top && p.y < r.bottom;
}