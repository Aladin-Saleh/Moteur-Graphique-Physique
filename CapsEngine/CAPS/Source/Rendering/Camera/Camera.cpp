#include "Camera.hpp"
#include "CameraManager.hpp"

namespace Ge
{
	void Camera::updatePerspective()
	{
		if (m_ortho)
		{
			m_perspective = glm::ortho(0.0f, (float)m_vulkanSwapChainMisc->str_swapChainExtent.width, (float)m_vulkanSwapChainMisc->str_swapChainExtent.height, 0.0f, m_near, m_far);
		}
		else
		{
			m_perspective = glm::perspective(glm::radians(m_fov), m_vulkanSwapChainMisc->str_swapChainExtent.width / (float)m_vulkanSwapChainMisc->str_swapChainExtent.height, m_near, m_far);
		}
		m_perspective[1][1] *= -1;
	}

	Camera::Camera(VulkanSwapChainMisc * vM) : GObject(true)
	{
		m_far = 500.0f;
		m_fov = 70.0f;
		m_near = 0.1f;
		m_priority = 0;
		m_vulkanSwapChainMisc = vM;
		Camera::updatePerspective();
	}

	void Camera::setFieldOfView(float fov)
	{
		m_fov = fov;
		Camera::updatePerspective();
	}

	void Camera::setNear(float n)
	{
		m_near = n;
		Camera::updatePerspective();
	}

	void Camera::setFar(float f)
	{
		m_far = f;
		Camera::updatePerspective();
	}

	void Camera::setPriority(int p)
	{
		m_priority = p;
		CameraManager::updateSelectCamera();
	}

	void Camera::setOrtho(bool state)
	{
		m_ortho = state;
		Camera::updatePerspective();
	}

	float Camera::getFieldOfView()
	{
		return m_fov;
	}

	float Camera::getNear()
	{
		return m_near;
	}

	float Camera::getFar()
	{
		return m_far;
	}

	int Camera::getPriority()
	{
		return m_priority;
	}

	glm::mat4 Camera::getView()
	{
		m_view = m_transform.rotationMatrix * m_transform.translateMatrix;
		return m_view;
	}

	glm::mat4 Camera::getProjection()
	{
		return m_perspective;
	}
}