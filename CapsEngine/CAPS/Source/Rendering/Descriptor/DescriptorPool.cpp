#include "DescriptorPool.hpp"

namespace Ge
{
	bool DescriptorPool::Initialize(VulkanMisc * vM)
	{
		std::vector<VkImage> swapChainImages = vM->str_VulkanSwapChainMisc->str_swapChainImages;
		std::array<VkDescriptorPoolSize, 6> poolSizes{};
		poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSizes[0].descriptorCount = static_cast<uint32_t>(swapChainImages.size()*(vM->str_VulkanDescriptor->modelCount == 0 ? 1 : vM->str_VulkanDescriptor->modelCount));
		poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		poolSizes[1].descriptorCount = static_cast<uint32_t>(swapChainImages.size()* (vM->str_VulkanDescriptor->TextureCount == 0 ? 1 : vM->str_VulkanDescriptor->TextureCount));
		poolSizes[2].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSizes[2].descriptorCount = static_cast<uint32_t>(swapChainImages.size() * vM->str_VulkanDescriptor->materialCount);
		poolSizes[3].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSizes[3].descriptorCount = static_cast<uint32_t>(swapChainImages.size() * vM->str_VulkanDescriptor->lightCount);
		poolSizes[4].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSizes[4].descriptorCount = static_cast<uint32_t>(swapChainImages.size());
		poolSizes[5].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		poolSizes[5].descriptorCount = static_cast<uint32_t>(swapChainImages.size());
		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
		poolInfo.pPoolSizes = poolSizes.data();
		poolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size());

		if (vkCreateDescriptorPool(vM->str_VulkanDeviceMisc->str_device, &poolInfo, nullptr, &m_descriptorPool) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'un descriptor pool");
			return false;
		}
		vM->str_VulkanDescriptor->str_descriptorPool = m_descriptorPool;
		Debug::Info("Initialisation du DescriptorPoolManager");
		return true;
	}

	bool DescriptorPool::InitializeImGuiPool(VulkanMisc * vM)
	{
		std::vector<VkImage> swapChainImages = vM->str_VulkanSwapChainMisc->str_swapChainImages;
		VkDescriptorPoolSize pool_sizes[] =
		{
			{ VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
			{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
			{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
			{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
		};

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = static_cast<uint32_t>(11);
		poolInfo.pPoolSizes = pool_sizes;
		poolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size());

		if (vkCreateDescriptorPool(vM->str_VulkanDeviceMisc->str_device, &poolInfo, nullptr, &m_ImGUIdescriptorPool) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'un descriptor pool pour ImGUI");
			return false;
		}

		vM->str_VulkanDescriptor->str_imGUIdescriptorPool = m_ImGUIdescriptorPool;
		Debug::Info("Initialisation du DescriptorPoolManagerImGui");
		return true;
	}

	void DescriptorPool::Release(VkDevice device)
	{
		vkDestroyDescriptorPool(device, m_descriptorPool, nullptr);
		Debug::Info("Liberation du DescriptorPoolManager");
	}

	void DescriptorPool::ReleaseImGuiPool(VkDevice device)
	{
		vkDestroyDescriptorPool(device, m_ImGUIdescriptorPool, nullptr);
	}
}
