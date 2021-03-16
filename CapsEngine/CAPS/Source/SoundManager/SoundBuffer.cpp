#include "SoundBuffer.hpp"

namespace Ge
{

	SoundBuffer::SoundBuffer() 
	{
		m_format  = 0;
		m_frequency = 0;
		m_sizei = 0;
		m_bufferID = 0;
	}

	SoundBuffer::~SoundBuffer()
	{
		alDeleteBuffers(1, &m_bufferID);
	}

	void SoundBuffer::Initialize(ALuint bufferID, ALenum format, ALsizei frequency, ALsizei msizei)
	{
		m_bufferID = bufferID;
		m_format = format;
		m_frequency = frequency;
		m_sizei = msizei;
		//alGenBuffers(1, &m_bufferID);
		//alBufferData(bufferID, format, data, msizei, frequency);
	}

	unsigned int SoundBuffer::GetID() const {
		return m_bufferID;
	}

	ALenum SoundBuffer::GetFormat() const {
		return m_format;
	}

	ALenum SoundBuffer::GetFrequency() const {
		return m_frequency;
	}

	ALsizei SoundBuffer::GetSize() const {
		return m_sizei;
	}
	
}	