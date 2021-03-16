#ifndef __CAPS_FRAME_BUFFERS__
#define __CAPS_FRAME_BUFFERS__

#include "Debug.hpp"
#include <array>
#include "VulkanMisc.hpp"

namespace Ge
{
	class FrameBuffers
	{
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanMisc * mV);
		void Release(VkDevice device);
	private:
		std::vector<VkFramebuffer> m_swapChainFramebuffers;
	};
}

#endif // !__CAPS_FRAME_BUFFERS__
