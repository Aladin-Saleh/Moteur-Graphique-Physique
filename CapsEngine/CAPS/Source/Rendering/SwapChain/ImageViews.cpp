#include "ImageViews.hpp"

namespace Ge
{
	bool ImageViews::Initialize(std::vector<VkImage>* SwapChainImage, VkFormat swapChainImageFormat, VulkanMisc * vM)
	{
		m_swapChainImageViews.resize(SwapChainImage->size());

		for (uint32_t i = 0; i < SwapChainImage->size(); i++)
		{
			m_swapChainImageViews[i] = createImageView((*SwapChainImage)[i], swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1, vM->str_VulkanDeviceMisc);
		}		
		vM->str_VulkanSwapChainMisc->str_swapChainImageViews = m_swapChainImageViews;
		return true;
	}
	
	void ImageViews::Release(VulkanDeviceMisc * vM)
	{
		for (auto imageView : m_swapChainImageViews)
		{
			vkDestroyImageView(vM->str_device, imageView, nullptr);
		}
	}
	
	VkImageView ImageViews::createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels, VulkanDeviceMisc * vM)
	{
		VkImageViewCreateInfo viewInfo{};
		viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewInfo.image = image;
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewInfo.format = format;
		viewInfo.subresourceRange.aspectMask = aspectFlags;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.levelCount = mipLevels;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.subresourceRange.layerCount = 1;

		VkImageView imageView;
		if (vkCreateImageView(vM->str_device, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'une image vue");
		}

		return imageView;
	}
}