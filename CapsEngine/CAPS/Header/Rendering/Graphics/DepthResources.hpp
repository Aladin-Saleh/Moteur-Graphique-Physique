#ifndef __CAPS_DEPTH_RESOURCES__
#define __CAPS_DEPTH_RESOURCES__

#include "VulkanMisc.hpp"

namespace Ge
{
	class DepthResources
	{
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanMisc * vM);
		void Release(VkDevice device);
	private:
		VkImage m_depthImage;
		VkDeviceMemory m_depthImageMemory;
		VkImageView m_depthImageView;
	};
}

#endif//!__CAPS_DEPTH_RESOURCES__