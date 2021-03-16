#ifndef __CAPS_INTERFACE_AUDIO__
#define __CAPS_INTERFACE_AUDIO__

#include "GraphicsObject.hpp"

class Audio : public virtual GraphicsObject
{
public:
	virtual void Play() = 0;
	virtual void Stop() = 0;
	virtual void Pause() = 0;
	virtual void SetLooping(bool bLoop) = 0;
	virtual void SetVolume(float volume) = 0;
	virtual void SetPitch(float pitch) = 0;
	virtual void SetVelocity(Vector3 velocity) = 0;
	virtual bool IsPlaying() const = 0;
	virtual bool IsLooping() const = 0;
	virtual float GetVolume() const = 0;
	virtual float GetPitch() const = 0;
	virtual Vector3 GetVelocity() const = 0;
	virtual void SetSoundBuffer(const char* bufferID) = 0;
};

#endif // !__CAPS_INTERFACE_AUDIO__
