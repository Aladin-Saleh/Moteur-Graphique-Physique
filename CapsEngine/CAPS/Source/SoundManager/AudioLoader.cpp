#include "AudioLoader.hpp"
#include "AudioData.hpp"

namespace Ge
{
	AudioData AudioLoader::LoadWav(const char* fi)
	{
		FILE* fp = NULL;
		fp = fopen(fi, "rb");

		char type[4];
		DWORD size, chunkSize;
		short formatType, channels;
		DWORD sampleRate, avgBytesPerSec;
		short bytesPerSample, bitsPerSample;
		DWORD dataSize;

		AudioData ad;
		ALenum format = 0;

		fread(type, sizeof(char), 4, fp);
		if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')
		{
			throw std::runtime_error("Le fichier audio n'est pas un RIFF");
		}
		fread(&size, sizeof(DWORD), 1, fp);
		fread(type, sizeof(char), 4, fp);
		if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')
		{
			throw std::runtime_error("Le fichier audio n'est pas un WAVE");
		}
		fread(type, sizeof(char), 4, fp);
		if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')
		{
			throw std::runtime_error("Le fichier audio n'est pas un fmt");
		}
		fread(&chunkSize, sizeof(DWORD), 1, fp);
		fread(&formatType, sizeof(short), 1, fp);
		fread(&channels, sizeof(short), 1, fp);
		fread(&sampleRate, sizeof(DWORD), 1, fp);
		fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
		fread(&bytesPerSample, sizeof(short), 1, fp);
		fread(&bitsPerSample, sizeof(short), 1, fp);
		fread(type, sizeof(char), 4, fp);
		if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')
		{
			throw std::runtime_error("Fichier audio data manquant.");
		}
		fread(&dataSize, sizeof(DWORD), 1, fp);
		unsigned char* buf = new unsigned char[dataSize];
		fread(buf, sizeof(BYTE), dataSize, fp);
		fclose(fp);

		if (bitsPerSample == 8)
		{
			if (channels == 1)
			{
				format = AL_FORMAT_MONO8;
			}
			else if (channels == 2)
			{
				format = AL_FORMAT_STEREO8;
			}
		}
		else if (bitsPerSample == 16)
		{
			if (channels == 1)
			{
				format = AL_FORMAT_MONO16;
			}
			else if (channels == 2)
			{
				format = AL_FORMAT_STEREO16;
			}
		}

		ad.format = format;
		ad.frequency = sampleRate;
		ad.data = buf;
		ad.size = dataSize;

		return ad;

	}

}
