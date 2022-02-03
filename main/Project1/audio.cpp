
#include "main.h"
#include "audio.h"





IXAudio2*				Audio::m_Xaudio = NULL;
IXAudio2MasteringVoice*	Audio::m_MasteringVoice = NULL;

AudioParam Audio::sedata[(unsigned int)SE::SEMAX] = {
		{"Asset\\Audio\\shot.wav",false},
		{"Asset\\Audio\\shot2.wav",false}, 
		{"Asset\\Audio\\hit.wav",false},
		{"Asset\\Audio\\cursor.wav",false},
		{"Asset\\Audio\\cursor.wav",false},
		{"Asset\\Audio\\ex.wav",false},
};

AudioParam Audio::bgmdata[(unsigned int)SE::SEMAX] = {
		{"Asset\\Audio\\main.wav",true},
		{"Asset\\Audio\\Pseudoscience.wav",true},
};

Audio* Audio::se[(unsigned int)SE::SEMAX];
Audio* Audio::bgm[(unsigned int)BGM::BGMMAX];

void Audio::InitMaster()
{
	// COM������
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio����
	XAudio2Create(&m_Xaudio, 0);

	// �}�X�^�����O�{�C�X����
	m_Xaudio->CreateMasteringVoice(&m_MasteringVoice);

	for (int i = 0; i < (unsigned int)SE::SEMAX; i++) {
		se[i] = new Audio();
		se[i]->Load(sedata[i].pFilename);
	}
	for (int i = 0; i < (unsigned int)BGM::BGMMAX; i++) {
		bgm[i] = new Audio();
		bgm[i]->Load(bgmdata[i].pFilename);
	}
}


void Audio::UninitMaster()
{
	m_MasteringVoice->DestroyVoice();
	m_Xaudio->Release();
	CoUninitialize();
}

void Audio::Load(const char *FileName)
{

	// �T�E���h�f�[�^�Ǎ�wav�̂�
	WAVEFORMATEX wfx = { 0 };

	{
		HMMIO hmmio = NULL;
		MMIOINFO mmioinfo = { 0 };
		MMCKINFO riffchunkinfo = { 0 };
		MMCKINFO datachunkinfo = { 0 };
		MMCKINFO mmckinfo = { 0 };
		UINT32 buflen;
		LONG readlen;


		hmmio = mmioOpen((LPSTR)FileName, &mmioinfo, MMIO_READ);
		assert(hmmio);

		riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(hmmio, &riffchunkinfo, NULL, MMIO_FINDRIFF);

		mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hmmio, &mmckinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		if (mmckinfo.cksize >= sizeof(WAVEFORMATEX))
		{
			mmioRead(hmmio, (HPSTR)&wfx, sizeof(wfx));
		}
		else
		{
			PCMWAVEFORMAT pcmwf = { 0 };
			mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
			memset(&wfx, 0x00, sizeof(wfx));
			memcpy(&wfx, &pcmwf, sizeof(pcmwf));
			wfx.cbSize = 0;
		}
		mmioAscend(hmmio, &mmckinfo, 0);

		datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hmmio, &datachunkinfo, &riffchunkinfo, MMIO_FINDCHUNK);



		buflen = datachunkinfo.cksize;
		m_SoundData = new unsigned char[buflen];
		readlen = mmioRead(hmmio, (HPSTR)m_SoundData, buflen);


		m_Length = readlen;
		m_PlayLength = readlen / wfx.nBlockAlign;


		mmioClose(hmmio, 0);
	}


	// �T�E���h�\�[�X����
	m_Xaudio->CreateSourceVoice(&m_SourceVoice, &wfx);
	assert(m_SourceVoice);
}


void Audio::Uninit()
{	
	if (m_SourceVoice != nullptr) {
		m_SourceVoice->Stop();
		m_SourceVoice->DestroyVoice();
	}
	delete[] m_SoundData;
}





void Audio::Play(bool Loop)
{
	m_SourceVoice->Stop();
	m_SourceVoice->FlushSourceBuffers();


	// �o�b�t�@�ݒ�
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = m_Length;
	bufinfo.pAudioData = m_SoundData;
	bufinfo.PlayBegin = 0;
	bufinfo.PlayLength = m_PlayLength;

	// ���[�v�ݒ�
	if (Loop)
	{
		bufinfo.LoopBegin = 0;
		bufinfo.LoopLength = m_PlayLength;
		bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	m_SourceVoice->SubmitSourceBuffer(&bufinfo, NULL);


	// �Đ�
	m_SourceVoice->Start();

}

void Audio::PlaySE(SE num)
{
	se[(unsigned int)num]->Play(sedata[(unsigned int)num].Loop);
}


void Audio::PlayBGM(BGM num)
{
	bgm[(unsigned int)num]->Play(bgmdata[(unsigned int)num].Loop);
}

void Audio::StopBGM(BGM num)
{
	bgm[(unsigned int)num]->m_SourceVoice->Stop();
}

