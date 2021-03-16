#ifndef __CAPS_AUDIO_DATA__
#define __CAPS_AUDIO_DATA__

#include "AL/al.h"
#include "glm/glm.hpp"
#include "AudioLoader.hpp"

struct AudioData {
	unsigned long size;
	ALuint source;
	ALuint buffer;
	ALuint frequency;
	ALenum format;
	unsigned char* data;
};

#endif //!__CAPS_AUDIO_DATA__
