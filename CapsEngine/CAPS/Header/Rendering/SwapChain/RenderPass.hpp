#ifndef __CASP_RENDER_PASS__
#define __CASP_RENDER_PASS__

#include "Debug.hpp"
#include <array>
#include "VulkanMisc.hpp"

namespace Ge
{
	class RenderPass
	{
	private:
		friend class SwapChain;
		bool Initialize(VkFormat swapChainImageFormat, VkSampleCountFlagBits msaaSamples, VulkanMisc * vM);
		void Release(VulkanDeviceMisc * vM);
	public:
		static VkFormat findDepthFormat(VulkanDeviceMisc * vM);
		static VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, VulkanDeviceMisc * vM);
	private:
		VkRenderPass m_renderPass;
		VkRenderPass m_renderPassSkybox;
	};
}

#endif//!__CASP_RENDER_PASS__