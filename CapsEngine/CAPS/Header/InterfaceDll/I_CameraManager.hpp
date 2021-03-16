#ifndef __CAPS_INTERFACE_CAMERA_MANAGER__
#define __CAPS_INTERFACE_CAMERA_MANAGER__

#include "I_Camera.hpp"

class I_CameraManager
{
public:
	virtual I_Camera * AllocateCamera(std::string name = "Camera") = 0;
	virtual void ReleaseCamera(I_Camera * camera) = 0;
	virtual I_Camera * getCurrentCamera() = 0;
};

#endif//!__CAPS_INTERFACE_CAMERA_MANAGER__