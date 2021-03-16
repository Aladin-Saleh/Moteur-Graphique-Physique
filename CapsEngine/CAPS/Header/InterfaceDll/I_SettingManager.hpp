#ifndef __CAPS_INTERFACE_SETTING_MANAGER__
#define __CAPS_INTERFACE_SETTING_MANAGER__

#include "Vector3.hpp"
#include "Vector4.hpp"
#include "SettingManagerStruct.hpp"

class I_SettingManager
{
public:
	virtual double GetFps() = 0;
	virtual void SetFps(double fps) = 0;
	virtual const char * GetName() = 0;
	virtual void SetName(const char * name) = 0;
	virtual double GetWindowHeight() = 0;
	virtual void SetWindowHeight(double height) = 0;
	virtual double GetWindowWidth() = 0;
	virtual void SetWindowWidth(double Width) = 0;
	virtual Vector3 GetGravity() = 0;
	virtual void SetGravity(Vector3 gravity) = 0;
	virtual void SetVersion(version v) = 0;
	virtual version GetVersion() = 0;
	virtual void SetClearColor(Vector4 color) = 0;
	virtual Vector4 GetClearColor() = 0;
	virtual void SetGamma(float gamma) = 0;
	virtual float GetGamma() = 0;
};

#endif //!__CAPS_INTERFACE_SETTING_MANAGER__