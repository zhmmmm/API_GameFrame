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
		//��ǰ����
		if (GetAsyncKeyState(i) & 0x8000)
		{
			//����ղ�Ϊ�ſ�
			if (_KS_CU == m_KeyState[i] || _KS_KU == m_KeyState[i])
				m_KeyState[i] = _KS_CD;
			//����ղ�Ϊ����
			else
				m_KeyState[i] = _KS_KD;
		}
		//��ǰ�ſ�
		else
		{
			//����ղ�Ϊ�ſ�
			if (_KS_CU == m_KeyState[i] || _KS_KU == m_KeyState[i])
				m_KeyState[i] = _KS_KU;
			//����ղ�Ϊ����
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
	//�õ���������������
	POINT p;
	GetCursorPos(&p);

	//������������ת��Ϊ���ڵĿͻ�������
	ScreenToClient(m_hWnd, &p);

	//���ý��
	*x = p.x;
	*y = p.y;

	//�õ����ڵĿͻ�������
	RECT r;
	GetClientRect(m_hWnd, &r);
	return p.x >= r.left && p.x < r.right && p.y >= r.top && p.y < r.bottom;
}