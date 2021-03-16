#ifndef __CAPS_LOGICAL_DEVICES__
#define __CAPS_LOGICAL_DEVICES__

#include "PhysicalDevices.hpp"
#include "ValidationLayer.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "VulkanMisc.hpp"

namespace Ge
{
	class LogicalDevice
	{
	private:
		VkQueue m_graphicsQueue;
		VkDevice m_device;
	public:
		friend class RenderingEngine;
		bool Initialize(VulkanDeviceMisc * vDM, WindowSurface * m_windowSurface);
		void Release(VulkanDeviceMisc * vDM);
	};
}

#endif