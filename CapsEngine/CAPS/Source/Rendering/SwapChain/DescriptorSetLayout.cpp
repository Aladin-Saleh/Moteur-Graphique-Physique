#include "DescriptorSetLayout.hpp"

namespace Ge
{
	bool DescriptorSetLayout::Initialize(VulkanMisc * vM)
	{
		VkDescriptorSetLayoutBinding uboLayoutBinding{};
		uboLayoutBinding.binding = 0;
		uboLayoutBinding.descriptorCount = (vM->str_VulkanDescriptor->modelCount == 0 ? 1 : vM->str_VulkanDescriptor->modelCount);
		uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboLayoutBinding.pImmutableSamplers = nullptr;
		uboLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;

		VkDescriptorSetLayoutBinding samplerLayoutBinding{};
		samplerLayoutBinding.binding = 1;
		samplerLayoutBinding.descriptorCount = (vM->str_VulkanDescriptor->TextureCount == 0 ? 1 : vM->str_VulkanDescriptor->TextureCount);
		samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		samplerLayoutBinding.pImmutableSamplers = nullptr;
		samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;

		VkDescriptorSetLayoutBinding ubmLayoutBinding{};
		ubmLayoutBinding.binding = 2;
		ubmLayoutBinding.descriptorCount = (vM->str_VulkanDescriptor->materialCount == 0 ? 1 : vM->str_VulkanDescriptor->materialCount);
		ubmLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		ubmLayoutBinding.pImmutableSamplers = nullptr;
		ubmLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;

		VkDescriptorSetLayoutBinding ublLayoutBinding{};
		ublLayoutBinding.binding = 3;
		ublLayoutBinding.descriptorCount = (vM->str_VulkanDescriptor->lightCount == 0 ? 1 : vM->str_VulkanDescriptor->lightCount);
		ublLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		ublLayoutBinding.pImmutableSamplers = nullptr;
		ublLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;

		VkDescriptorSetLayoutBinding ubdLayoutBinding{};
		ubdLayoutBinding.binding = 4;
		ubdLayoutBinding.descriptorCount = 1;
		ubdLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		ubdLayoutBinding.pImmutableSamplers = nullptr;
		ubdLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;

		VkDescriptorSetLayoutBinding samplerLayoutBindingShadowMap{};
		samplerLayoutBindingShadowMap.binding = 5;
		samplerLayoutBindingShadowMap.descriptorCount = 1;
		samplerLayoutBindingShadowMap.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		samplerLayoutBindingShadowMap.pImmutableSamplers = nullptr;
		samplerLayoutBindingShadowMap.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;

		std::array<VkDescriptorSetLayoutBinding, 6> bindings = { uboLayoutBinding, samplerLayoutBinding, ubmLayoutBinding, ublLayoutBinding, ubdLayoutBinding, samplerLayoutBindingShadowMap };

		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
		layoutInfo.pBindings = bindings.data();

		if (vkCreateDescriptorSetLayout(vM->str_VulkanDeviceMisc->str_device, &layoutInfo, nullptr, &m_descriptorSetLayout) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation du descriptor set layout");
			return false;
		}
		vM->str_VulkanSwapChainMisc->str_descriptorSetLayout = m_descriptorSetLayout;
		return true;
	}

	void DescriptorSetLayout::Release(VulkanDeviceMisc * vM)
	{
		vkDestroyDescriptorSetLayout(vM->str_device, m_descriptorSetLayout, nullptr);
	}
}