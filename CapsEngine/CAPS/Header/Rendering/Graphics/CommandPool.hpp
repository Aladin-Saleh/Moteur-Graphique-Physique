#ifndef __CAPS_COMMAND_POOL__
#define __CAPS_COMMAND_POOL__

#include "Debug.hpp"
#include <vector>
#include "VulkanMisc.hpp"

namespace Ge
{
	class CommandPool
	{
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanDeviceMisc * vM, VulkanCommandeBufferMisc * vCM);
		void Release(VulkanDeviceMisc * vM);
	private:
		VkCommandPool m_commandPool;
	};
}

#endif//!__CAPS_COMMAND_POOL__