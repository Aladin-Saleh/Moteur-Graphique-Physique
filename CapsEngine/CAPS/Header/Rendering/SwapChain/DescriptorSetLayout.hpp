#ifndef __CAPS_DESCRIPTOR_SET_LAYOUT__
#define __CAPS_DESCRIPTOR_SET_LAYOUT__

#include "Debug.hpp"
#include <array>
#include "VulkanMisc.hpp"

namespace Ge
{
	class DescriptorSetLayout
	{
	private:
		friend class SwapChain;
		bool Initialize(VulkanMisc * vM);
		void Release(VulkanDeviceMisc * vM);
	private:
		VkDescriptorSetLayout m_descriptorSetLayout;
	};
}

#endif//!__CAPS_DESCRIPTOR_SET_LAYOUT__