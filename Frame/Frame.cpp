#include "Frame.h"
#include <windows.h>

//��������
void FrameInit();
void FrameRun();
void FrameEnd();
void GameSetClientAndFPS(int*, int*, int*);
void GameInit();
void GameRun();
void GameEnd();

//���ھ��
HWND g_hWnd = NULL;

//����
BOOL g_Active = FALSE;

//�ͻ�����
int g_ClientW = 0;

//�ͻ�����
int g_ClientH = 0;

//ÿ֡ʱ��
int g_FrameTime = 0;

//����
CGameInput* g_GameInput = NULL;

//���
CGameOutput* g_GameOutput = NULL;

//��Ƶ
CGameAudio* g_GameAudio = NULL;

//������Ϣ����
LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam)
{
	switch (uMsg)
	{
		//������Ϣ
	case WM_ACTIVATEAPP:
		{
			g_Active = (BOOL)wParam;
			return 0;
		}

		//������Ϣ
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	//�����ĵ���Ϣʹ��Ĭ�ϴ���
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	//��䴰�����ṹ��
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

	//ע�ᴰ�����ṹ��
	RegisterClass(&wc);

	//��������
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

	//���ÿͻ�����֡��
	g_ClientW = 640;
	g_ClientH = 480;
	int fps = 40;
	GameSetClientAndFPS(&g_ClientW, &g_ClientH, &fps);
	g_FrameTime = 1000 / fps;

	//���ݿͻ������μ��㴰�ھ���
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

	//��������
	MoveWindow(g_hWnd, r.left, r.top, r.right - r.left, r.bottom - r.top, TRUE);

	//��ʼ��
	FrameInit();

	//��ʾ����
	ShowWindow(g_hWnd, nCmdShow);

	//���´���
	UpdateWindow(g_hWnd);


	//��Ϸѭ��
	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		//����Ϣ
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			//������Ϣ
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//����Ϣ���ڻ
		else if (g_Active)
		{
			//�õ���֡��ʼʱ��
			int bt = GetTickCount();

			//����
			FrameRun();

			//��֡��Ϣ
			int at = GetTickCount() - bt;
			Sleep(g_FrameTime > at ? g_FrameTime - at : 1);
		}
		//����Ϣ���ڷǻ
		else
			//�ȴ���Ϣ
			WaitMessage();
	}

	//����
	FrameEnd();

	return (int)msg.wParam;
}

void FrameInit()
{
	//��������
	g_GameInput = new CGameInput(g_hWnd);
	g_GameOutput = new CGameOutput(g_hWnd);
	g_GameAudio = new CGameAudio();

	//��Ϸ��ʼ��
	GameInit();
}

void FrameRun()
{
	//��������
	g_GameInput->Run();

	//��Ƶ����
	g_GameAudio->Run();

	//��ʼ����
	g_GameOutput->BeginOutput();

	//��Ϸ����
	GameRun();

	//��������
	g_GameOutput->EndOutput();
}

void FrameEnd()
{
	//��Ϸ����
	GameEnd();

	//ɾ������
	delete g_GameAudio;
	delete g_GameOutput;
	delete g_GameInput;
}

void GameExit()
{
	PostQuitMessage(0);
}