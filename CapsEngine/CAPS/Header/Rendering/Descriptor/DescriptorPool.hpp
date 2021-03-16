#ifndef __CAPS__DESCRIPTOR_POOL__
#define __CAPS__DESCRIPTOR_POOL__

#include "Debug.hpp"
#include <vector>
#include "VulkanMisc.hpp"

namespace Ge
{

	class DescriptorPool
	{
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanMisc * vM);
		bool InitializeImGuiPool(VulkanMisc * vM);
		void Release(VkDevice device);
		void ReleaseImGuiPool(VkDevice device);
	private:
		VkDescriptorPool m_descriptorPool;
		VkDescriptorPool m_ImGUIdescriptorPool;
	};
}

#endif //!__CAPS__DESCRIPTOR_POOL__
