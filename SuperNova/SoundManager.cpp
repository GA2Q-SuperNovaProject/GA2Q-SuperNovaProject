#include "SoundManager.h"

FMOD::System* SoundManager::m_pSystem;
FMOD::Sound* SoundManager::m_pSound[100];
FMOD::Channel* SoundManager::m_pChannel[100];
float SoundManager::m_volume;

SoundManager::~SoundManager()
{
	delete m_pSystem;
	delete[] m_pSound;
	delete[] m_pChannel;
}

void SoundManager::Initialize()
{
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(100, FMOD_INIT_NORMAL, nullptr);
}


void SoundManager::CreateSound(const char* soundFile, eSoundChannel soundChannel, bool isLoop)
{
	if (isLoop)
	{
		m_pSystem->createSound(soundFile, FMOD_LOOP_NORMAL, 0, &m_pSound[soundChannel]);
	}
	else
	{
		m_pSystem->createSound(soundFile, FMOD_LOOP_OFF, 0, &m_pSound[soundChannel]);
	}
}

void SoundManager::PlaySounds(eSoundChannel soundChannel)
{
	m_pSystem->playSound(m_pSound[soundChannel], nullptr, false, &m_pChannel[soundChannel]);
}

void SoundManager::StopSound(eSoundChannel soundChannel)
{
	m_pChannel[soundChannel]->setPaused(true);
}

void SoundManager::StopAllSound()
{
	for (int i = 0; i < 100; i++)
	{
		if (m_pChannel[i] != nullptr)
		{
			m_pChannel[i]->setPaused(true);
		}
	}
}

void SoundManager::SetSoundVolume(eSoundChannel soundChannel, float volume)
{
	m_pChannel[soundChannel]->setVolume(m_volume);
}

void SoundManager::SoundVolumeUp(eSoundChannel soundChannel, float volume)
{
	m_volume += volume;
	m_pChannel[soundChannel]->setVolume(m_volume);
}

void SoundManager::SoundVolumeDown(eSoundChannel soundChannel, float volume)
{
	m_volume -= volume;
	m_pChannel[soundChannel]->setVolume(m_volume);
}


