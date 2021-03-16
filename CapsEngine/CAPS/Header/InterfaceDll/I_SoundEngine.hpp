#ifndef __CAPS_INTERFACE_SOUND_ENGINE__
#define __CAPS_INTERFACE_SOUND_ENGINE__

#include "Audio.hpp"

class I_SoundEngine
{
public:
	virtual bool CreateSoundBuffer(const char* file, const char* audioID) = 0;
	virtual Audio* AllocateAudioSource(std::string name = "AudioSource") = 0;
	virtual void ReleaseAudioSource(Audio*& pSource) = 0;
	virtual void ReleaseSoundBuffer(const char * audioID) = 0;
};

#endif//!__CAPS_INTERFACE_SOUND_ENGINE__