#ifndef __SOUND_ENGINE__
#define __SOUND_ENGINE__

#include "Debug.hpp"
#include "SoundBuffer.hpp"
#include "SoundBufferManager.hpp"
#include "AudioSource.hpp"
#include "AudioLoader.hpp"
#include "AudioData.hpp"
#include <vector>
#include <algorithm>
//#include "AudioListener.hpp"
#include "I_SoundEngine.hpp"

namespace Ge
{

	class SoundEngine : public I_SoundEngine
	{
	public:
		bool CreateSoundBuffer(const char* file, const char* audioID);
		//void CreateAudioListener();
		//AudioListener* GetAudioListener();
		Audio* AllocateAudioSource(std::string name = "AudioSource");
		void ReleaseAudioSource(Audio*& pSource);
		void ReleaseSoundBuffer(const char* audioID);
		std::vector<AudioSource*> getAudioSources();
	private:
		friend class GameEngine;
		bool Initialize();
		void Release();

	private:
		ALCdevice*  m_pDevice;
		ALCcontext* m_pContext;
		//AudioListener* m_pAudioListener;
		std::vector<AudioSource*> m_audioSources;
		SoundBufferManager m_soundBufferManager;
	};
}
#endif