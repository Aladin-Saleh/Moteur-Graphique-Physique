#ifndef __CAPS_INSTANCE_V__
#define __CAPS_INSTANCE_V__

#include "vulkan/vulkan.h"
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include "ValidationLayer.hpp"
#include "VulkanMisc.hpp"

namespace Ge
{
	class InstanceV
	{
	private:
		friend class RenderingEngine;
		bool InitInstance(const char * name, version v, VulkanDeviceMisc * vDM);
		void Release();
	private:
		VkInstance instance;
		static std::vector<const char*> instanceExtensions;
	};
}
#endif //__CAPS_INSTANCE_V__