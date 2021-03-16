#ifndef __CAPS_AUDIO_LOADER__
#define __CAPS_AUDIO_LOADER__

#include <stdio.h>
#include <stdlib.h>

#include "Debug.hpp"
#include "AL/al.h"
#include "AL/alc.h"
#include "glm/glm.hpp"
#include "AudioData.hpp"


typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef struct AudioData AudioData;

namespace Ge
{
	class AudioLoader
	{
	public:
		static AudioData LoadWav(const char*);

	};
}

#endif