#ifndef _FRAME_H_
#define _FRAME_H_

#include "GameInput.h"
#include "GameOutput.h"
#include "GameAudio.h"

//输入器指针
extern CGameInput* g_GameInput;

//输出器指针
extern CGameOutput* g_GameOutput;

//音频器指针
extern CGameAudio* g_GameAudio;



//退出函数
void GameExit();

#endif