#include "GameOutput.h"
#include <string.h>

#pragma comment(lib, "Msimg32.lib")

HDC	g_GameHDC = NULL;

CGameOutput::CGameOutput(HWND hWnd)
:
m_hWnd(hWnd)
{
	//得到客户区宽、高
	RECT r;
	GetClientRect(m_hWnd, &r);
	m_ClientPW = r.right - r.left;
	m_ClientPH = r.bottom - r.top;

	//得到主设备
	m_MainDC = GetDC(m_hWnd);

	HBITMAP hbmp = 0;

	//创建后备设备
	m_BackDC = CreateCompatibleDC(m_MainDC);
	g_GameHDC = m_BackDC;
	//如果要开启windows平台的矩阵变换支持，需要将绘图模式改变为高级模式
	SetGraphicsMode(m_BackDC,GM_ADVANCED);
	hbmp = CreateCompatibleBitmap(m_MainDC, m_ClientPW, m_ClientPH);
	DeleteObject(SelectObject(m_BackDC, hbmp));

	//设置后备设备
	SetBkMode(m_BackDC, TRANSPARENT);
}

CGameOutput::~CGameOutput()
{
	//释放所有位图
	for (int i = 0; i < (int)m_Images.size(); ++i)
	{
		if (0 != m_Images[i])
			DeleteDC(m_Images[i]);
	}

	//释放所有字体
	for (int i = 0; i < (int)m_Fonts.size(); ++i)
	{
		if (0 != m_Fonts[i])
			DeleteObject(m_Fonts[i]);
	}

	//删除后备设备
	DeleteDC(m_BackDC);

	//释放主设备
	ReleaseDC(m_hWnd, m_MainDC);
}

void CGameOutput::BeginOutput()
{
	//将后备设备清空为白色
	BitBlt(m_BackDC, 0, 0, m_ClientPW, m_ClientPH, 0, 0, 0, WHITENESS);
}

void CGameOutput::EndOutput()
{
	//将后备设备颜色数据拷贝给主设备
	BitBlt(m_MainDC, 0, 0, m_ClientPW, m_ClientPH, m_BackDC, 0, 0, SRCCOPY);
}

void CGameOutput::DrawLine(int x1,
						   int y1,
						   int x2,
						   int y2,
						   int color)
{
	//创建画笔
	HPEN p1 = CreatePen(PS_SOLID, 1, color);

	//选入新画笔得到老画笔
	HPEN p0 = (HPEN)SelectObject(m_BackDC, p1);

	//绘制线段
	MoveToEx(m_BackDC, x1, y1, 0);
	LineTo(m_BackDC, x2, y2);

	//将老画笔选回
	SelectObject(m_BackDC, p0);

	//删除新画笔
	DeleteObject(p1);
}

void CGameOutput::DrawRectangle(int x1,
								int y1,
								int x2,
								int y2,
								int color1,
								int color2)
{
	//创建画笔、画刷
	HPEN p1 = CreatePen(PS_SOLID, 1, color1);
	HBRUSH b1 = CreateSolidBrush(color2);

	//选入新画笔、画刷得到老画笔、画刷
	HPEN p0 = (HPEN)SelectObject(m_BackDC, p1);
	HBRUSH b0 = (HBRUSH)SelectObject(m_BackDC, b1);

	//绘制矩形
	Rectangle(m_BackDC, x1, y1, x2, y2);

	//将老画笔、画刷选回
	SelectObject(m_BackDC, p0);
	SelectObject(m_BackDC, b0);

	//删除新画笔、画刷
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
	//创建画笔、画刷
	HPEN p1 = CreatePen(PS_SOLID, 1, color1);
	HBRUSH b1 = CreateSolidBrush(color2);

	//选入新画笔、画刷得到老画笔、画刷
	HPEN p0 = (HPEN)SelectObject(m_BackDC, p1);
	HBRUSH b0 = (HBRUSH)SelectObject(m_BackDC, b1);

	//绘制圆形
	Ellipse(m_BackDC, x1, y1, x2, y2);

	//将老画笔、画刷选回
	SelectObject(m_BackDC, p0);
	SelectObject(m_BackDC, b0);

	//删除新画笔、画刷
	DeleteObject(p1);
	DeleteObject(b1);
}

int CGameOutput::LoadFont(int w,
						  int h,
						  const char* f)
{
	//创建字体
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

	//放入字体表
	for (int i = 0; i < (int)m_Fonts.size(); ++i)
	{
		if (0 == m_Fonts[i])
		{
			m_Fonts[i] = font;
			return i;
		}
	}
	m_Fonts.push_back(font);

	//返回该字体下标
	return (int)m_Fonts.size() - 1;
}

bool CGameOutput::ReleaseFont(int index)
{
	//下标越界
	if (index < 0 || index >= (int)m_Fonts.size())
		return false;

	//字体为空
	if (0 == m_Fonts[index])
		return false;

	//删除字体并设置为空
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
	//得到指定字体是否存在
	bool find = index >= 0 && index < (int)m_Fonts.size() && 0 != m_Fonts[index];

	//如果存在字体就选入
	HFONT f0 = 0;
	if (find)
		f0 = (HFONT)SelectObject(m_BackDC, m_Fonts[index]);

	//设置字体颜色
	SetTextColor(m_BackDC, color);

	//绘制文字
	TextOutA(m_BackDC, x, y, t, (int)strlen(t));

	//将老的字体选入
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
	//得到指定字体是否存在
	bool find = index >= 0 && index < (int)m_Fonts.size() && 0 != m_Fonts[index];

	//如果存在字体就选入
	HFONT f0 = 0;
	if (find)
		f0 = (HFONT)SelectObject(m_BackDC, m_Fonts[index]);

	//设置字体颜色
	SetTextColor(m_BackDC, color);

	//绘制文字
	RECT r = {x1, y1, x2, y2};
	DrawTextA(m_BackDC, t, (int)strlen(t), &r, DT_WORDBREAK);

	//将老的字体选入
	if (find)
		SelectObject(m_BackDC, f0);
}

int CGameOutput::LoadBmp(const char* fn)
{
	//加载位图
	HBITMAP hbmp = (HBITMAP)LoadImageA(
		0,
		fn,
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE);
	if (0 == hbmp)
		return -1;

	//创建兼容设备
	HDC hdc = CreateCompatibleDC(m_MainDC);

	//选入位图到兼容设备
	DeleteObject(SelectObject(hdc, hbmp));

	//入表
	m_Images.push_back(hdc);

	return (int)m_Images.size() - 1;
}

//卸载位图
bool CGameOutput::ReleaseBmp(int index)
{
	//下标越界
	if (index < 0 || index >= (int)m_Images.size())
		return false;

	//字体为空
	if (0 == m_Images[index])
		return false;

	//删除字体并设置为空
	DeleteDC(m_Images[index]);
	m_Images[index] = 0;

	return true;
}

bool CGameOutput::DrawBmp1(int index,//加载图片返回的图片ID
						   int dx, //表示在窗口客户区的位置
						   int dy, 
						   int dw, //表示要画多宽
						   int dh,//表示要画多高
						   int sx, //图片上要画到屏幕上的起点位置
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