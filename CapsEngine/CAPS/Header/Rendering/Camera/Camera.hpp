#ifndef __CAPS_CAMERA__
#define __CAPS_CAMERA__

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include "Vector3.hpp"
#include "I_Camera.hpp"
#include "VulkanMisc.hpp"
#include "GObject.hpp"

namespace Ge
{
	class Camera : public I_Camera, public virtual GObject
	{
	private:
		friend class CameraManager;
		void updatePerspective();
	public:
		Camera(VulkanSwapChainMisc * vM);
		void setFieldOfView(float fov);
		void setNear(float near);
		void setFar(float far);
		void setPriority(int p);
		void setOrtho(bool state);
		float getFieldOfView();
		float getNear();
		float getFar();
		int getPriority();
		glm::mat4 getView();
		glm::mat4 getProjection();
	private:
		VulkanSwapChainMisc * m_vulkanSwapChainMisc;
		glm::mat4 m_perspective;
		glm::mat4 m_view;
		float m_fov = 70.0f;
		float m_near = 0.1f;
		float m_far = 300.0f;
		int m_priority = 0;
		bool m_ortho = false;
	};
}

#endif//!__CAPS_CAMERA__