#include "GameOutput.h"
#include <string.h>

#pragma comment(lib, "Msimg32.lib")

HDC	g_GameHDC = NULL;

CGameOutput::CGameOutput(HWND hWnd)
:
m_hWnd(hWnd)
{
	//�õ��ͻ�������
	RECT r;
	GetClientRect(m_hWnd, &r);
	m_ClientPW = r.right - r.left;
	m_ClientPH = r.bottom - r.top;

	//�õ����豸
	m_MainDC = GetDC(m_hWnd);

	HBITMAP hbmp = 0;

	//�������豸
	m_BackDC = CreateCompatibleDC(m_MainDC);
	g_GameHDC = m_BackDC;
	//���Ҫ����windowsƽ̨�ľ���任֧�֣���Ҫ����ͼģʽ�ı�Ϊ�߼�ģʽ
	SetGraphicsMode(m_BackDC,GM_ADVANCED);
	hbmp = CreateCompatibleBitmap(m_MainDC, m_ClientPW, m_ClientPH);
	DeleteObject(SelectObject(m_BackDC, hbmp));

	//���ú��豸
	SetBkMode(m_BackDC, TRANSPARENT);
}

CGameOutput::~CGameOutput()
{
	//�ͷ�����λͼ
	for (int i = 0; i < (int)m_Images.size(); ++i)
	{
		if (0 != m_Images[i])
			DeleteDC(m_Images[i]);
	}

	//�ͷ���������
	for (int i = 0; i < (int)m_Fonts.size(); ++i)
	{
		if (0 != m_Fonts[i])
			DeleteObject(m_Fonts[i]);
	}

	//ɾ�����豸
	DeleteDC(m_BackDC);

	//�ͷ����豸
	ReleaseDC(m_hWnd, m_MainDC);
}

void CGameOutput::BeginOutput()
{
	//�����豸���Ϊ��ɫ
	BitBlt(m_BackDC, 0, 0, m_ClientPW, m_ClientPH, 0, 0, 0, WHITENESS);
}

void CGameOutput::EndOutput()
{
	//�����豸��ɫ���ݿ��������豸
	BitBlt(m_MainDC, 0, 0, m_ClientPW, m_ClientPH, m_BackDC, 0, 0, SRCCOPY);
}

void CGameOutput::DrawLine(int x1,
						   int y1,
						   int x2,
						   int y2,
						   int color)
{
	//��������
	HPEN p1 = CreatePen(PS_SOLID, 1, color);

	//ѡ���»��ʵõ��ϻ���
	HPEN p0 = (HPEN)SelectObject(m_BackDC, p1);

	//�����߶�
	MoveToEx(m_BackDC, x1, y1, 0);
	LineTo(m_BackDC, x2, y2);

	//���ϻ���ѡ��
	SelectObject(m_BackDC, p0);

	//ɾ���»���
	DeleteObject(p1);
}

void CGameOutput::DrawRectangle(int x1,
								int y1,
								int x2,
								int y2,
								int color1,
								int color2)
{
	//�������ʡ���ˢ
	HPEN p1 = CreatePen(PS_SOLID, 1, color1);
	HBRUSH b1 = CreateSolidBrush(color2);

	//ѡ���»��ʡ���ˢ�õ��ϻ��ʡ���ˢ
	HPEN p0 = (HPEN)SelectObject(m_BackDC, p1);
	HBRUSH b0 = (HBRUSH)SelectObject(m_BackDC, b1);

	//���ƾ���
	Rectangle(m_BackDC, x1, y1, x2, y2);

	//���ϻ��ʡ���ˢѡ��
	SelectObject(m_BackDC, p0);
	SelectObject(m_BackDC, b0);

	//ɾ���»��ʡ���ˢ
	DeleteObject(p1);
	DeleteObject(b1);
}

void CGameOutput::DrawEllipse(int x1,
							  int y1,
							  int x2,
							  int y2,
							  int color1,
							  int color2)
{
	//�������ʡ���ˢ
	HPEN p1 = CreatePen(PS_SOLID, 1, color1);
	HBRUSH b1 = CreateSolidBrush(color2);

	//ѡ���»��ʡ���ˢ�õ��ϻ��ʡ���ˢ
	HPEN p0 = (HPEN)SelectObject(m_BackDC, p1);
	HBRUSH b0 = (HBRUSH)SelectObject(m_BackDC, b1);

	//����Բ��
	Ellipse(m_BackDC, x1, y1, x2, y2);

	//���ϻ��ʡ���ˢѡ��
	SelectObject(m_BackDC, p0);
	SelectObject(m_BackDC, b0);

	//ɾ���»��ʡ���ˢ
	DeleteObject(p1);
	DeleteObject(b1);
}

int CGameOutput::LoadFont(int w,
						  int h,
						  const char* f)
{
	//��������
	HFONT font = CreateFontA(
		h,
		w,
		0,
		0,
		FW_NORMAL,
		false,
		false,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		f);

	//���������
	for (int i = 0; i < (int)m_Fonts.size(); ++i)
	{
		if (0 == m_Fonts[i])
		{
			m_Fonts[i] = font;
			return i;
		}
	}
	m_Fonts.push_back(font);

	//���ظ������±�
	return (int)m_Fonts.size() - 1;
}

bool CGameOutput::ReleaseFont(int index)
{
	//�±�Խ��
	if (index < 0 || index >= (int)m_Fonts.size())
		return false;

	//����Ϊ��
	if (0 == m_Fonts[index])
		return false;

	//ɾ�����岢����Ϊ��
	DeleteObject(m_Fonts[index]);
	m_Fonts[index] = 0;

	return true;
}

void CGameOutput::DrawString1(int index,
							  int x,
							  int y,
							  const char* t,
							  int color)
{
	//�õ�ָ�������Ƿ����
	bool find = index >= 0 && index < (int)m_Fonts.size() && 0 != m_Fonts[index];

	//������������ѡ��
	HFONT f0 = 0;
	if (find)
		f0 = (HFONT)SelectObject(m_BackDC, m_Fonts[index]);

	//����������ɫ
	SetTextColor(m_BackDC, color);

	//��������
	TextOutA(m_BackDC, x, y, t, (int)strlen(t));

	//���ϵ�����ѡ��
	if (find)
		SelectObject(m_BackDC, f0);
}

void CGameOutput::DrawString2(int index,
							  int x1,
							  int y1,
							  int x2,
							  int y2,
							  const char* t,
							  int color)
{
	//�õ�ָ�������Ƿ����
	bool find = index >= 0 && index < (int)m_Fonts.size() && 0 != m_Fonts[index];

	//������������ѡ��
	HFONT f0 = 0;
	if (find)
		f0 = (HFONT)SelectObject(m_BackDC, m_Fonts[index]);

	//����������ɫ
	SetTextColor(m_BackDC, color);

	//��������
	RECT r = {x1, y1, x2, y2};
	DrawTextA(m_BackDC, t, (int)strlen(t), &r, DT_WORDBREAK);

	//���ϵ�����ѡ��
	if (find)
		SelectObject(m_BackDC, f0);
}

int CGameOutput::LoadBmp(const char* fn)
{
	//����λͼ
	HBITMAP hbmp = (HBITMAP)LoadImageA(
		0,
		fn,
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE);
	if (0 == hbmp)
		return -1;

	//���������豸
	HDC hdc = CreateCompatibleDC(m_MainDC);

	//ѡ��λͼ�������豸
	DeleteObject(SelectObject(hdc, hbmp));

	//���
	m_Images.push_back(hdc);

	return (int)m_Images.size() - 1;
}

//ж��λͼ
bool CGameOutput::ReleaseBmp(int index)
{
	//�±�Խ��
	if (index < 0 || index >= (int)m_Images.size())
		return false;

	//����Ϊ��
	if (0 == m_Images[index])
		return false;

	//ɾ�����岢����Ϊ��
	DeleteDC(m_Images[index]);
	m_Images[index] = 0;

	return true;
}

bool CGameOutput::DrawBmp1(int index,//����ͼƬ���ص�ͼƬID
						   int dx, //��ʾ�ڴ��ڿͻ�����λ��
						   int dy, 
						   int dw, //��ʾҪ�����
						   int dh,//��ʾҪ�����
						   int sx, //ͼƬ��Ҫ������Ļ�ϵ����λ��
						   int sy)
{
	if (index < 0 || index >= (int)m_Images.size() || 0 == m_Images[index])
		return false;

	BitBlt(
		m_BackDC,
		dx, dy, dw, dh,
		m_Images[index],
		sx, sy,
		SRCCOPY);

	return true;
}

bool CGameOutput::DrawBmp2(int index,
						   int dx, int dy, int dw, int dh,
						   int sx, int sy, int sw, int sh,
						   int tc)
{
	if (index < 0 || index >= (int)m_Images.size() || 0 == m_Images[index])
		return false;

	TransparentBlt(
		m_BackDC,
		dx, dy, dw, dh,
		m_Images[index],
		sx, sy, sw, sh,
		tc);

	return true;
}

int CGameOutput::GetClientPW()
{
	return m_ClientPW;
}

int CGameOutput::GetClientPH()
{
	return m_ClientPH;
}

HDC CGameOutput::GetBackHDC()
{
	return m_BackDC;
}