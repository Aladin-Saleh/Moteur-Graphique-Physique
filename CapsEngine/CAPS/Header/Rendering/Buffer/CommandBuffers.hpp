#ifndef __CAPS_COMMAND_BUFFERS__
#define __CAPS_COMMAND_BUFFERS__

#include "Debug.hpp"
#include <vector>
#include "VulkanMisc.hpp"
#include  "Model_Manager.hpp"
#include "ShadowManager.hpp"

namespace Ge
{
	class CommandBuffers
	{
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanMisc * vM, Model_Manager * mM, ShadowManager * sM);
		void Release(VulkanMisc * vM);
	public:
		static VkCommandBuffer beginSingleTimeCommands(VulkanMisc * vM);
		static void endSingleTimeCommands(VkCommandBuffer commandBuffer, VulkanMisc * vM);
	private:
		std::vector<VkCommandBuffer> m_commandBuffers;
	};
}
#endif // !__CAPS_COMMAND_BUFFERS__
