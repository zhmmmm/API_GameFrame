#include "Frame.h"
#include <windows.h>

//函数声明
void FrameInit();
void FrameRun();
void FrameEnd();
void GameSetClientAndFPS(int*, int*, int*);
void GameInit();
void GameRun();
void GameEnd();

//窗口句柄
HWND g_hWnd = NULL;

//活动标记
BOOL g_Active = FALSE;

//客户区宽
int g_ClientW = 0;

//客户区高
int g_ClientH = 0;

//每帧时间
int g_FrameTime = 0;

//输入
CGameInput* g_GameInput = NULL;

//输出
CGameOutput* g_GameOutput = NULL;

//音频
CGameAudio* g_GameAudio = NULL;

//窗口消息函数
LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam)
{
	switch (uMsg)
	{
		//激活消息
	case WM_ACTIVATEAPP:
		{
			g_Active = (BOOL)wParam;
			return 0;
		}

		//销毁消息
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	//不关心的消息使用默认处理
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	//填充窗口类别结构体
	WNDCLASS wc
		=
	{
		CS_HREDRAW | CS_VREDRAW,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(0, IDI_APPLICATION),
		LoadCursor(0, IDC_ARROW),
		(HBRUSH)COLOR_WINDOW,
		0,
		__TEXT("Frame")
	};

	//注册窗口类别结构体
	RegisterClass(&wc);

	//创建窗口
	g_hWnd = CreateWindow(
		wc.lpszClassName,
		__TEXT(""),
		WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		HWND_DESKTOP,
		0,
		wc.hInstance,
		0);

	//设置客户区和帧率
	g_ClientW = 640;
	g_ClientH = 480;
	int fps = 40;
	GameSetClientAndFPS(&g_ClientW, &g_ClientH, &fps);
	g_FrameTime = 1000 / fps;

	//根据客户区矩形计算窗口矩形
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	RECT r =
	{
		(sw - g_ClientW) / 2,
		(sh - g_ClientH) / 2,
		r.left + g_ClientW,
		r.top + g_ClientH
	};
	AdjustWindowRect(
		&r,
		WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 
		FALSE);

	//调整窗口
	MoveWindow(g_hWnd, r.left, r.top, r.right - r.left, r.bottom - r.top, TRUE);

	//初始化
	FrameInit();

	//显示窗口
	ShowWindow(g_hWnd, nCmdShow);

	//更新窗口
	UpdateWindow(g_hWnd);


	//游戏循环
	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		//有消息
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			//处理消息
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//无消息窗口活动
		else if (g_Active)
		{
			//得到本帧起始时间
			int bt = GetTickCount();

			//运行
			FrameRun();

			//本帧休息
			int at = GetTickCount() - bt;
			Sleep(g_FrameTime > at ? g_FrameTime - at : 1);
		}
		//无消息窗口非活动
		else
			//等待消息
			WaitMessage();
	}

	//结束
	FrameEnd();

	return (int)msg.wParam;
}

void FrameInit()
{
	//创建工具
	g_GameInput = new CGameInput(g_hWnd);
	g_GameOutput = new CGameOutput(g_hWnd);
	g_GameAudio = new CGameAudio();

	//游戏初始化
	GameInit();
}

void FrameRun()
{
	//输入运行
	g_GameInput->Run();

	//音频运行
	g_GameAudio->Run();

	//开始绘制
	g_GameOutput->BeginOutput();

	//游戏运行
	GameRun();

	//结束绘制
	g_GameOutput->EndOutput();
}

void FrameEnd()
{
	//游戏结束
	GameEnd();

	//删除工具
	delete g_GameAudio;
	delete g_GameOutput;
	delete g_GameInput;
}

void GameExit()
{
	PostQuitMessage(0);
}