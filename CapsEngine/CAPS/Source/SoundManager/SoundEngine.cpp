#include "SoundEngine.hpp"

namespace Ge
{
	bool SoundEngine::Initialize()
	{	
		m_pDevice = alcOpenDevice(nullptr);
		if (!m_pDevice)
		{
			Debug::Warn("Echec il y a aucun pheripherique audio!");
			return true;
		}
		m_pContext = alcCreateContext(m_pDevice, nullptr);
		alcMakeContextCurrent(m_pContext);
		if (!m_pContext)
		{
			Debug::Error("�chec de la cr�ation du context audio!");
			return false;
		}
		Debug::Info("Initialisation du SoundEngine");
		return true;
	}

	void SoundEngine::Release() 
	{
		for (AudioSource * as : m_audioSources)
		{
			delete(as);
		}
		m_soundBufferManager.Release();
		alcMakeContextCurrent(NULL);
		alcDestroyContext(m_pContext);
		alcCloseDevice(m_pDevice);
		Debug::Info("Liberation du SoundEngine");
	}

	bool SoundEngine::CreateSoundBuffer(const char* file, const char* audioID) {
		struct AudioData dataStruct = AudioLoader::LoadWav(file);
		ALuint buffer;
		alGenBuffers(1, &buffer);
		alBufferData(buffer, dataStruct.format, dataStruct.data, dataStruct.size, dataStruct.frequency);
		SoundBuffer * soundBuffer = new SoundBuffer();
		soundBuffer->Initialize(buffer, dataStruct.format, dataStruct.frequency, dataStruct.size);
		m_soundBufferManager.Register(audioID, soundBuffer);
		Debug::Info("Create Sound Buffer %s , %s",nullptr, file, audioID);
		return true;
	}

	Audio* SoundEngine::AllocateAudioSource(std::string name)
	{
		AudioSource* au = new AudioSource(&m_soundBufferManager);
		au->setName(name);
		m_audioSources.push_back(au);
		return au;
	}

	void SoundEngine::ReleaseAudioSource(Audio*& pSource) 
	{		
		AudioSource * as;
		for (int i = 0; i < m_audioSources.size(); i++)
		{
			if ((Audio*)m_audioSources[i] == pSource)
			{
				as = m_audioSources[i];
				m_audioSources.erase(m_audioSources.begin() + i);
				delete(as);
			}
		}
	}

	void SoundEngine::ReleaseSoundBuffer(const char * audioID)
	{
		m_soundBufferManager.Unregister(audioID);
	}

	std::vector<AudioSource*> SoundEngine::getAudioSources()
	{
		return m_audioSources;
	}

}