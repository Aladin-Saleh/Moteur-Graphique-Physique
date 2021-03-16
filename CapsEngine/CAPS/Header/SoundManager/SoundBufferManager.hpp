#ifndef __CAPS_SOUND_BUFFER_MANAGER__
#define __CAPS_SOUND_BUFFER_MANAGER__

#include "Debug.hpp"
#include "SoundBuffer.hpp"
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include "AL/al.h"

namespace Ge
{
	class SoundBufferManager
	{
	public:
		void Register(const std::string& bufferKey, SoundBuffer * buffer);
		void Unregister(const std::string& bufferKey);
		SoundBuffer * GetBuffer(const std::string& bufferKey);
		void Release();
	private:
		std::unordered_map<std::string, SoundBuffer *> m_bufferIDs;
		typedef std::pair<const std::string&, SoundBuffer *> Couple;
		std::vector<SoundBuffer *> m_bufferV;
	};
}

#endif

