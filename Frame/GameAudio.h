#ifndef _GAME_AUDIO_H_
#define _GAME_AUDIO_H_

#include <vector>

//����MCI��Media Control Interface����mp3��Ƶ������
class CGameAudio
{
	friend void FrameInit();
	friend void FrameRun();
	friend void FrameEnd();

	//��������
	char m_CurMusic;

	//��������
	int m_MusicVolume;

	//��Ч
	int m_Effect;

	//��Ч��
	std::vector<int> m_Effects;

	//��Ч����
	int m_EffectVolume;

	//�����
	char m_Buf1[256];
	char m_Buf2[256];

	//��׺�����
	bool _check_mp3(const char* fn);

	//����
	CGameAudio();

	//����
	~CGameAudio();

	//����
	void Run();

public:

	//����ָ����������
	bool PlayMusic(const char* fn);

	//��ͣ��������
	bool PauseMusic();

	//�ָ���������
	bool ResumeMusic();

	//ֹͣ��������
	bool StopMusic();

	//�õ�������������
	int GetMusicVolume();

	//���ñ�������������1~1000��
	void SetMusicVolume(int volume);
	
	//����ָ����Ч
	bool PlayEffect(const char* fn);

	//�õ���Ч����
	int GetEffectVolume();

	//������Ч������1~1000��
	void SetEffectVolume(int volume);
};

#endif