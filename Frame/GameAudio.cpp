#include "GameAudio.h"
#include <iostream>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "Winmm.lib")

bool CGameAudio::_check_mp3(const char* fn)
{
	const char* p = NULL;
	if (p = strrchr(fn, '.'))
	{
		strcpy_s(m_Buf1, 256, p + 1);
		for (int i = 0; m_Buf1[i] != 0; ++i)
		{
			if (m_Buf1[i] >= 'A' && m_Buf1[i] <= 'Z')
				m_Buf1[i] += 'a' - 'A';
		}
		return strcmp(m_Buf1, "mp3") == 0;
	}
	else
		return false;
}

CGameAudio::CGameAudio()
:
m_CurMusic(0),
m_MusicVolume(500),
m_Effect(0),
m_EffectVolume(500)
{}

CGameAudio::~CGameAudio()
{
	///�رձ�������
	if (0 != m_CurMusic)
	{
		sprintf_s(m_Buf1, 256, "close %c", m_CurMusic);
		mciSendStringA(m_Buf1, m_Buf2, 256, 0);
	}

	///�ر�����û�в�����ϵ���Ч
	for (std::vector<int>::iterator it = m_Effects.begin(); it != m_Effects.end(); ++it)
	{
		sprintf_s(m_Buf1, 256, "close %d", *it);
		mciSendStringA(m_Buf1, m_Buf2, 256, 0);
	}
}

bool CGameAudio::PlayMusic(const char* fn)
{
	if (!_check_mp3(fn))
		return false;

	///�õ���ǰ�����ֺ�Ҫ���ŵ�����
	char cm = m_CurMusic;
	char pm = m_CurMusic != 'a' ? 'a' : 'b';

	///��Ҫ���ŵ�����
	sprintf_s(m_Buf1, 256, "open %s Alias %c", fn, pm);
	if (0 != mciSendStringA(m_Buf1, m_Buf2, 256, 0))
	{
		m_CurMusic = cm;
		return false;
	}

	///�رյ�ǰ������
	if (cm != 0)
	{
		sprintf_s(m_Buf1, 256, "close %c", cm);
		mciSendStringA(m_Buf1, m_Buf2, 256, 0);
	}

	///����Ҫ���ŵ����ֵ�����
	sprintf_s(m_Buf1, 256, "setaudio %c volume to %d", pm, m_MusicVolume);
	mciSendStringA(m_Buf1, m_Buf2, 256, 0);

	///����
	sprintf_s(m_Buf1, 256, "play %c repeat", pm);
	mciSendStringA(m_Buf1, m_Buf2, 256, 0);
	
	///��������
	m_CurMusic = pm;

	return true;
}

bool CGameAudio::PauseMusic()
{
	if (0 == m_CurMusic)
		return false;

	///��ͣ��������
	sprintf_s(m_Buf1, 256, "pause %c", m_CurMusic);
	mciSendStringA(m_Buf1, m_Buf2, 256, 0);

	return true;
}

bool CGameAudio::ResumeMusic()
{
	if (0 == m_CurMusic)
		return false;

	///�ָ���������
	sprintf_s(m_Buf1, 256, "resume %c", m_CurMusic);
	mciSendStringA(m_Buf1, m_Buf2, 256, 0);

	return true;
}

bool CGameAudio::StopMusic()
{
	if (0 == m_CurMusic)
		return false;

	///�رձ�������
	sprintf_s(m_Buf1, 256, "close %c", m_CurMusic);
	mciSendStringA(m_Buf1, m_Buf2, 256, 0);
	m_CurMusic = 0;

	return true;
}

int CGameAudio::GetMusicVolume()
{
	return m_MusicVolume;
}

void CGameAudio::SetMusicVolume(int volume)
{
	if (volume < 1)
		volume = 1;
	else if (volume > 1000)
		volume = 1000;
	m_MusicVolume = volume;
	if (m_CurMusic != 0)
	{
		sprintf_s(m_Buf1, 256, "setaudio %c volume to %d", m_CurMusic, m_MusicVolume);
		mciSendStringA(m_Buf1, m_Buf2, 256, 0);
	}
}

bool CGameAudio::PlayEffect(const char* fn)
{
	if (!_check_mp3(fn))
		return false;

	m_Effect += 1;

	///����Ч
	sprintf_s(m_Buf1, 256, "open %s Alias %d", fn, m_Effect);
	if (0 != mciSendStringA(m_Buf1, m_Buf2, 256, 0))
	{
		m_Effect -= 1;
		return false;
	}

	///������Ч����
	sprintf_s(m_Buf1, 256, "setaudio %d volume to %d", m_Effect, m_EffectVolume);
	mciSendStringA(m_Buf1, m_Buf2, 256, 0);

	///����
	sprintf_s(m_Buf1, 256, "play %d", m_Effect);
	mciSendStringA(m_Buf1, m_Buf2, 256, 0);

	///���
	m_Effects.push_back(m_Effect);

	return true;
}

int CGameAudio::GetEffectVolume()
{
	return m_EffectVolume;
}

void CGameAudio::SetEffectVolume(int volume)
{
	if (volume < 1)
		volume = 1;
	else if (volume > 1000)
		volume = 1000;
	m_EffectVolume = volume;
}

void CGameAudio::Run()
{
	///�ر��Ѿ�ֹͣ����Ч
	for (std::vector<int>::iterator it = m_Effects.begin(); it != m_Effects.end(); )
	{
		sprintf_s(m_Buf1, 256, "status %d mode", *it);
		mciSendStringA(m_Buf1, m_Buf2, 256, 0);
		if (strcmp(m_Buf2, "stopped") == 0)
		{
			sprintf_s(m_Buf1, 256, "close %d", *it);
			mciSendStringA(m_Buf1, m_Buf2, 256, 0);
			it = m_Effects.erase(it);
		}
		else
			++it;
	}
}