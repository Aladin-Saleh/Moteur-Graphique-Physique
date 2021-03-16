#ifndef __CAPS_IMAGE_VIEWS__
#define __CAPS_IMAGE_VIEWS__

#include "Debug.hpp"
#include "VulkanMisc.hpp"

namespace Ge
{
	class ImageViews
	{
	public:
		bool Initialize(std::vector<VkImage> * SwapChainImage, VkFormat swapChainImageFormat, VulkanMisc * vM);
		void Release(VulkanDeviceMisc * vM);
	public:
		static VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels, VulkanDeviceMisc * vM);
	private:
		std::vector<VkImageView> m_swapChainImageViews;
	};
}

#endif//!__CAPS_IMAGE_VIEWS__