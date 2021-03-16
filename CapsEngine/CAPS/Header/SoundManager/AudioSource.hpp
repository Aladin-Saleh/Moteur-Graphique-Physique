#ifndef __AUDIO_SOURCE__
#define __AUDIO_SOURCE__

#include "Debug.hpp"
#include "SoundBuffer.hpp"
#include "AL/alc.h"
#include "Vector3.hpp"
#include "Audio.hpp"
#include "SoundBufferManager.hpp"
#include "GObject.hpp"

namespace Ge
{
	class AudioSource : public Audio, public virtual GObject
	{
	private:
		ALuint m_sourceID;
		bool m_bLoop = 0;
		float m_volume = 0;
		float m_pitch = 0;
		Vector3 m_position;
		Vector3 m_velocity;
		SoundBuffer * m_buffer;
		SoundBufferManager * m_soundBufferManager;
		int style_idx = -1;
	public:
		AudioSource(SoundBufferManager * sM);
		~AudioSource();
		void Play();
		void Stop();
		void Pause();
		void SetLooping(bool bLoop);
		void SetVolume(float volume);
		void SetPitch(float pitch);
		void setPosition(Vector3 pos) override; 
		void SetVelocity(Vector3 velocity);
		void SetSoundBuffer(const char* bufferID);
		bool IsPlaying() const;
		bool IsLooping() const;
		float GetVolume() const;
		float GetPitch() const;
		void OnGUI() override;
		Vector3 getPosition() override;
		Vector3 GetVelocity() const;

	};
}

#endif