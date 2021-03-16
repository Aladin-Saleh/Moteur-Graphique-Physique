#include "ColorResources.hpp"
#include "PhysicalDevices.hpp"
#include "ImageViews.hpp"

namespace Ge
{
	bool ColorResources::Initialize(VulkanMisc * vM)
	{
		VkExtent2D swapChainExtent = vM->str_VulkanSwapChainMisc->str_swapChainExtent;

		if (!createImage(swapChainExtent.width, swapChainExtent.height, 1, PhysicalDevices::getMaxUsableSampleCount(vM->str_VulkanDeviceMisc), vM->str_VulkanSwapChainMisc->str_swapChainImageFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_colorImage, m_colorImageMemory, vM->str_VulkanDeviceMisc))
		{
			return false;
		}
		m_colorImageView = ImageViews::createImageView(m_colorImage, vM->str_VulkanSwapChainMisc->str_swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1, vM->str_VulkanDeviceMisc);
		vM->str_VulkanCommandeBufferMisc->str_colorImageView = m_colorImageView;
		vM->str_VulkanCommandeBufferMisc->str_colorImage = m_colorImage;
		vM->str_VulkanCommandeBufferMisc->str_colorImageMemory = m_colorImageMemory;
		Debug::Info("Initialisation de la ColorResources");
		return true;
	}

	void ColorResources::Release(VkDevice device)
	{
		vkDestroyImageView(device, m_colorImageView, nullptr);
		vkDestroyImage(device, m_colorImage, nullptr);
		vkFreeMemory(device, m_colorImageMemory, nullptr);
		Debug::Info("Liberation du ColorResources");
	}

	bool ColorResources::createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory, VulkanDeviceMisc * vM)
	{
		VkImageCreateInfo imageInfo{};
		imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageInfo.imageType = VK_IMAGE_TYPE_2D;
		imageInfo.extent.width = width;
		imageInfo.extent.height = height;
		imageInfo.extent.depth = 1;
		imageInfo.mipLevels = mipLevels;
		imageInfo.arrayLayers = 1;
		imageInfo.format = format;
		imageInfo.tiling = tiling;
		imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		imageInfo.usage = usage;
		imageInfo.samples = numSamples;
		imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateImage(vM->str_device, &imageInfo, nullptr, &image) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'une image");
			return false;
		}

		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(vM->str_device, image, &memRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties, vM->str_physicalDevice);

		if (vkAllocateMemory(vM->str_device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS)
		{
			Debug::Error("Echec de l'allocation de la memoire d'une image");
			return false;
		}

		vkBindImageMemory(vM->str_device, image, imageMemory, 0);
		return true;
	}

	uint32_t ColorResources::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties,VkPhysicalDevice pDevice)
	{
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(pDevice, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
			{
				return i;
			}
		}

		Debug::Error("CAPS n'a pas reussi a trouver un type de memoire approprie");
	}
}