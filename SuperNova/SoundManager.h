#pragma once
#include "EnumDefine.h"
#include "fmod.hpp"

/// <summary>
/// SoundManager 
/// 2023.02.06 [MinseoChoi]
/// </summary>

class SoundManager
{
public:
	static void Initialize();
	static void CreateSound(const char* SoundFile, eSoundChannel soundChannel, bool isLoop);
	static void PlaySounds(eSoundChannel soundChannel);
	static void StopSound(eSoundChannel soundChannel);
	static void StopAllSound();
	static void SetSoundVolume(eSoundChannel soundChannel, float volume = 1.0f);
	static void SoundVolumeUp(eSoundChannel soundChannel, float volume = 1.0f);
	static void SoundVolumeDown(eSoundChannel soundChannel, float volume = 1.0f);

private:
	 SoundManager() {}
	 ~SoundManager();

	static FMOD::System* m_pSystem;
	static FMOD::Sound* m_pSound[100];
	static FMOD::Channel* m_pChannel[100];

	static float m_volume;
};

