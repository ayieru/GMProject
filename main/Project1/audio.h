#pragma once

#include <xaudio2.h>
#include "gameObject.h"

enum class SE {
	shot,
	shot2,
	hit,
	hit2,
	cursor,
	select,
	ex,
	SEMAX,
};

enum class BGM {
	main,
	game,
	boss,
	BGMMAX,
};

typedef struct
{
	const char* pFilename;	
	bool Loop;		
} AudioParam;

class Audio : public GameObject
{
private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	IXAudio2SourceVoice*	m_SourceVoice;
	BYTE*					m_SoundData;

	int						m_Length;
	int						m_PlayLength;

	static AudioParam sedata[];
	static AudioParam bgmdata[];

	static Audio* se[];
	static Audio* bgm[];

public:
	static void InitMaster();
	static void UninitMaster();

	void Init() {};
	void Uninit();
	void Update() {};
	void Draw() {};

	void Load(const char *FileName);
	void Play(bool Loop = false);

	void PlaySE(SE num);
	void PlayBGM(BGM num);
	void StopBGM(BGM num);
};

