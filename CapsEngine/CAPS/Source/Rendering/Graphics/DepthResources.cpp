#include "DepthResources.hpp"
#include "RenderPass.hpp"
#include "ColorResources.hpp"
#include "ImageViews.hpp"
#include "PhysicalDevices.hpp"

namespace Ge
{
	bool DepthResources::Initialize(VulkanMisc * vM)
	{
		VkFormat depthFormat = RenderPass::findDepthFormat(vM->str_VulkanDeviceMisc);
		vM->str_VulkanSwapChainMisc->str_depthFormat = depthFormat;
		VkExtent2D swapChainExtent = vM->str_VulkanSwapChainMisc->str_swapChainExtent;

		ColorResources::createImage(swapChainExtent.width, swapChainExtent.height, 1, PhysicalDevices::getMaxUsableSampleCount(vM->str_VulkanDeviceMisc), depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_depthImage, m_depthImageMemory, vM->str_VulkanDeviceMisc);
		m_depthImageView = ImageViews::createImageView(m_depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, 1, vM->str_VulkanDeviceMisc);
		Debug::Info("Initialisation de la DepthResources");
		vM->str_VulkanCommandeBufferMisc->str_depthImageView = m_depthImageView;
		return true;
	}

	void DepthResources::Release(VkDevice device)
	{
		vkDestroyImageView(device, m_depthImageView, nullptr);
		vkDestroyImage(device, m_depthImage, nullptr);
		vkFreeMemory(device, m_depthImageMemory, nullptr);
		Debug::Info("Liberation du DepthResources");
	}
}