#ifndef _GAME_AUDIO_H_
#define _GAME_AUDIO_H_

#include <vector>

//基于MCI（Media Control Interface）的mp3音频管理器
class CGameAudio
{
	friend void FrameInit();
	friend void FrameRun();
	friend void FrameEnd();

	//背景音乐
	char m_CurMusic;

	//音乐音量
	int m_MusicVolume;

	//音效
	int m_Effect;

	//音效表
	std::vector<int> m_Effects;

	//音效音量
	int m_EffectVolume;

	//命令缓冲
	char m_Buf1[256];
	char m_Buf2[256];

	//后缀名检查
	bool _check_mp3(const char* fn);

	//构造
	CGameAudio();

	//析构
	~CGameAudio();

	//运行
	void Run();

public:

	//播放指定背景音乐
	bool PlayMusic(const char* fn);

	//暂停背景音乐
	bool PauseMusic();

	//恢复背景音乐
	bool ResumeMusic();

	//停止背景音乐
	bool StopMusic();

	//得到背景音乐音量
	int GetMusicVolume();

	//设置背景音乐音量（1~1000）
	void SetMusicVolume(int volume);
	
	//播放指定音效
	bool PlayEffect(const char* fn);

	//得到音效音量
	int GetEffectVolume();

	//设置音效音量（1~1000）
	void SetEffectVolume(int volume);
};

#endif