#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_

#include <windows.h>
#include <vector>

//游戏窗口HDC
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

	//构造
	CGameOutput(HWND hWnd);

	//析构
	~CGameOutput();

	//0：二次缓冲
	void BeginOutput();
	void EndOutput();

public:

	//下面的函数中，只有LoadFont、LoadBmp是放在
	//游戏初始化函数中使用，其它所有函数都是应该
	//放在游戏循环中使用的

	//1：图元

	//绘制线段
	void DrawLine(
		int x1, //端点1的x坐标
		int y1, //端点1的y坐标
		int x2, //端点2的x坐标
		int y2, //端点2的y坐标
		int color); //颜色

	//绘制矩形
	void DrawRectangle(
		int x1, //左上角x坐标
		int y1, //左上角y坐标
		int x2, //右下角x坐标
		int y2, //右下角y坐标
		int color1, //描边颜色
		int color2); //填充颜色

	//绘制圆形
	void DrawEllipse(
		int x1, //左上角x坐标
		int y1, //左上角y坐标
		int x2, //右下角x坐标
		int y2, //右下角y坐标
		int color1, //描边颜色
		int color2); //填充颜色

	//作为文字而言，如果每次都是创建、绘制、销毁的话，它
	//的开销是比较大的，对于这种相比画刷、画笔占用更多内
	//存的资源，可以采取加载、使用、销毁的方式来进行管理
	//，同理位图也应该这样，注意加载应该在初始化阶段、使
	//用就是在游戏循环阶段、销毁是在游戏结束阶段来完成

	//2：文字

	//加载文字返回代表这个文字的整数id
	int LoadFont(
		int w, //字体宽
		int h, //字体高
		const char* f); //字体外观

	//卸载文字
	bool ReleaseFont(int index);

	//绘制单行文字
	void DrawString1(
		int index,
		int x,
		int y,
		const char* t,
		int color);

	//绘制多行文字
	void DrawString2(
		int index,
		int x1,
		int y1,
		int x2,
		int y2,
		const char* t,
		int color);

	//3：图像

	//加载位图
	int LoadBmp(const char* fn);

	//卸载位图
	bool ReleaseBmp(int index);

	//绘制位图1
	bool DrawBmp1(
		int index,//LoadBmp返回的图片ID
		int dx, int dy, int dw, int dh,//要绘制到窗口上什么矩形区域
		int sx, int sy);//资源图片上要绘制图片区域左上角坐标

	//绘制位图2
	bool DrawBmp2(
		int index,//LoadBmp返回的图片ID
		int dx, int dy, int dw, int dh,//要绘制到窗口上什么矩形区域
		int sx, int sy, int sw, int sh,//资源图片上要绘制图片矩形区域
		int tc);//绘制时要忽略掉的颜色

	//得到客户区宽
	int GetClientPW();

	//得到客户区高
	int GetClientPH();

	HDC GetBackHDC();
};

#endif