#ifndef __CAPS_SOUND_MANAGER_TEST__
#define __CAPS_SOUND_MANAGER_TEST__

#include <stdio.h>
#include <stdlib.h>

#include "Debug.hpp"
#include "SoundBuffer.hpp"
#include "SoundEngine.hpp"
#include "AL/al.h"
#include "AL/alc.h"

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;

namespace Ge
{
	class SoundManagerTest
	{
	public:
		bool Initialize();
		void Start();
	private:
		void LoadSound();
		void CreateContextAL();
		SoundBuffer m_soundBuffer;
		SoundEngine m_mySoundEngine;
	};
}

#endif