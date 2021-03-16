#ifndef __SOUND_BUFFER__
#define __SOUND_BUFFER__

#include "Debug.hpp"
#include "AL/al.h"

namespace Ge
{
	class SoundBuffer
	{
	private:
		ALuint m_bufferID;
		//unsigned char* buf;
		ALenum m_format;
		ALsizei m_frequency;
		ALsizei m_sizei;
	public:
		SoundBuffer();
		~SoundBuffer();
		void Initialize(ALuint bufferID, ALenum format, ALsizei frequency, ALsizei msizei);
		unsigned int GetID() const;
		ALenum GetFormat() const;
		ALenum GetFrequency() const;
		ALsizei GetSize() const;
	};
}

#endif