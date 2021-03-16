#ifndef __CAPS_FLY_CAMERA__
#define __CAPS_FLY_CAMERA__

#include "Camera.hpp"
#include "I_InputManager.hpp"

namespace Ge
{
	class FlyCamera
	{
	public:
		FlyCamera(I_InputManager * input, Camera * cam);
		void UpdateCamera();
	private:
		I_InputManager * iM;
		Camera * camera;
		float m_angleX;
		float m_angleY;
		float m_maxSpeed = 10.0f;
		float m_fastSpeedMult = 1.0f;
		float m_moveSpeed = 0.0f;
		float m_maxSpeedRotate = 0.2f;
		float m_addMoveSpeed = 0.0f;
	};
}

#endif //!__CAPS_FLY_CAMERA__