#ifndef __CAPS_WINDOW_SURFACE__
#define __CAPS_WINDOW_SURFACE__

#include "vulkan/vulkan.h"
#include "Debug.hpp"
#include "VulkanMisc.hpp"

namespace Ge
{
	class WindowSurface
	{
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanDeviceMisc * vDM);
		void Release(VulkanDeviceMisc * vDM);
	public:
		void SetupPresentQueue(VkDevice device, unsigned int value, VulkanDeviceMisc * vDM);
	private:
		friend class RenderingEngine;
		VkQueue m_presentQueue;
		VkSurfaceKHR m_surface;
	};
}

#endif //__CAPS_WINDOW_SURFACE__