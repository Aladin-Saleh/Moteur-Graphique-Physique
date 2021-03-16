#ifndef __CAPS_COLOR_RESOURCES__
#define __CAPS_COLOR_RESOURCES__

#include "Debug.hpp"
#include "VulkanMisc.hpp"

namespace Ge
{
	class ColorResources
	{
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanMisc * vM);
		void Release(VkDevice device);
	public:
		static bool createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory, VulkanDeviceMisc * vM);
		static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice pDevice);
	private:
		VkImageView m_colorImageView;
		VkImage m_colorImage;
		VkDeviceMemory m_colorImageMemory;
	};
}

#endif//!__CAPS_COLOR_RESOURCES__