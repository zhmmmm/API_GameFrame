#ifndef _FRAME_H_
#define _FRAME_H_

#include "GameInput.h"
#include "GameOutput.h"
#include "GameAudio.h"

//������ָ��
extern CGameInput* g_GameInput;

//�����ָ��
extern CGameOutput* g_GameOutput;

//��Ƶ��ָ��
extern CGameAudio* g_GameAudio;



//�˳�����
void GameExit();

#endif