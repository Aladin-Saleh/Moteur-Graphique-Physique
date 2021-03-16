#include "DescriptorSets.hpp"
using namespace Ge;

namespace Ge
{
	bool DescriptorSets::Initialize(VulkanMisc * vM, Model_Manager * mM, TextureManager * tM, MaterialManager * mMat, LightManager * lM, ShaderUBdiver* suD, ShadowManager * sM)
	{
		std::vector<VkImage> swapChainImages = vM->str_VulkanSwapChainMisc->str_swapChainImages;
		std::vector<MShape*> mesh = mM->getModels();
		std::vector<Textures*> textures = tM->getTextures();
		std::vector<Materials*> materials = mMat->GetMaterial();
		std::vector<Lights*> lights = lM->GetLights();
		VkDevice device = vM->str_VulkanDeviceMisc->str_device;
		std::vector<VkDescriptorSetLayout> layouts(swapChainImages.size(), vM->str_VulkanSwapChainMisc->str_descriptorSetLayout);
		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = vM->str_VulkanDescriptor->str_descriptorPool;
		allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImages.size());
		allocInfo.pSetLayouts = layouts.data();

		m_descriptorSets.resize(swapChainImages.size());
		if (vkAllocateDescriptorSets(device, &allocInfo, m_descriptorSets.data()) != VK_SUCCESS)
		{
			Debug::Error("Echec de l'allocation du descriptor sets");
			return false;
		}

		std::vector<VkDescriptorBufferInfo> bufferInfo{};
		VkDescriptorBufferInfo bufferI{};
		for (MShape * models : mesh)
		{
			bufferI.buffer = models->GetUniformBuffers();
			bufferI.offset = 0;
			bufferI.range = sizeof(UniformBufferObject);
			bufferInfo.push_back(bufferI);
		}
		if (bufferInfo.size() == 0)
		{
			bufferI.buffer = mM->getUniformBuffers();
			bufferI.offset = 0;
			bufferI.range = 8;
			bufferInfo.push_back(bufferI);
		}

		std::vector<VkDescriptorImageInfo> imageInfo{};
		VkDescriptorImageInfo imageI{};
		for (Textures * text : textures)
		{
			imageI.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageI.imageView = text->getVkImageView();
			imageI.sampler = text->getVkSampler();
			imageInfo.push_back(imageI);
		}
		if (imageInfo.size() == 0)
		{
			imageI.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageI.imageView = tM->getNTextures()->getVkImageView();
			imageI.sampler = tM->getNTextures()->getVkSampler();
			imageInfo.push_back(imageI);
		}

		std::vector<VkDescriptorBufferInfo> bufferInfoMaterial{};
		VkDescriptorBufferInfo bufferIM{};
		for (Materials * mat : materials)
		{
			bufferIM.buffer = mat->GetUniformBuffers();
			bufferIM.offset = 0;
			bufferIM.range = sizeof(UniformBufferMaterial);
			bufferInfoMaterial.push_back(bufferIM);
		}

		if (bufferInfoMaterial.size() == 0)//GetBaseMaterial()
		{
			bufferIM.buffer = mMat->GetBaseMaterial()->GetUniformBuffers();
			bufferIM.offset = 0;
			bufferIM.range = sizeof(UniformBufferMaterial);
			bufferInfoMaterial.push_back(bufferIM);
		}

		std::vector<VkDescriptorBufferInfo> bufferInfolights{};
		VkDescriptorBufferInfo bufferIL{};
		for (Lights * light : lights)
		{
			bufferIL.buffer = light->GetUniformBuffers();
			bufferIL.offset = 0;
			bufferIL.range = sizeof(UniformBufferLight);
			bufferInfolights.push_back(bufferIL);
		}

		std::vector<VkDescriptorBufferInfo> bufferMatrixlights{};
		VkDescriptorBufferInfo bufferML{};
		for (Lights * light : lights)
		{
			if (light->GetStatus() == 0)
			{
				bufferML.buffer = light->GetlightMatrixShadowUniformBuffers();
				bufferML.offset = 0;
				bufferML.range = sizeof(OffScreenShadow);
			}
		}
		bufferMatrixlights.push_back(bufferML);

		sM->UpdateDescriptorShadowMap(bufferMatrixlights, bufferInfo);

		std::vector<VkDescriptorBufferInfo> bufferInfoDivers{};
		VkDescriptorBufferInfo bufferIUBD{};
		bufferIUBD.buffer = suD->GetUniformBuffers();
		bufferIUBD.offset = 0;
		bufferIUBD.range = sizeof(UniformBufferDiver);
		bufferInfoDivers.push_back(bufferIUBD);

		std::vector<VkDescriptorImageInfo> imageInfoShadow{};
		VkDescriptorImageInfo imageIS{};
		imageIS.imageLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
		imageIS.imageView = sM->m_offscreenPass.depth.view;
		imageIS.sampler = sM->m_offscreenPass.depthSampler;
		imageInfoShadow.push_back(imageIS);
		
		
		for (size_t i = 0; i < swapChainImages.size(); i++)
		{
			std::array<VkWriteDescriptorSet, 6> descriptorWrites{};

			descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[0].dstSet = m_descriptorSets[i];
			descriptorWrites[0].dstBinding = 0;
			descriptorWrites[0].dstArrayElement = 0;
			descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrites[0].descriptorCount = static_cast<uint32_t>(bufferInfo.size());
			descriptorWrites[0].pBufferInfo = bufferInfo.data();

			descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[1].dstSet = m_descriptorSets[i];
			descriptorWrites[1].dstBinding = 1;
			descriptorWrites[1].dstArrayElement = 0;
			descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			descriptorWrites[1].descriptorCount = static_cast<uint32_t>(imageInfo.size());
			descriptorWrites[1].pImageInfo = imageInfo.data();

			descriptorWrites[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[2].dstSet = m_descriptorSets[i];
			descriptorWrites[2].dstBinding = 2;
			descriptorWrites[2].dstArrayElement = 0;
			descriptorWrites[2].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrites[2].descriptorCount = static_cast<uint32_t>(bufferInfoMaterial.size());
			descriptorWrites[2].pBufferInfo = bufferInfoMaterial.data();

			descriptorWrites[3].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[3].dstSet = m_descriptorSets[i];
			descriptorWrites[3].dstBinding = 3;
			descriptorWrites[3].dstArrayElement = 0;
			descriptorWrites[3].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrites[3].descriptorCount = static_cast<uint32_t>(bufferInfolights.size());
			descriptorWrites[3].pBufferInfo = bufferInfolights.data();

			descriptorWrites[4].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[4].dstSet = m_descriptorSets[i];
			descriptorWrites[4].dstBinding = 4;
			descriptorWrites[4].dstArrayElement = 0;
			descriptorWrites[4].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrites[4].descriptorCount = static_cast<uint32_t>(bufferInfoDivers.size());
			descriptorWrites[4].pBufferInfo = bufferInfoDivers.data();

			descriptorWrites[5].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[5].dstSet = m_descriptorSets[i];
			descriptorWrites[5].dstBinding = 5;
			descriptorWrites[5].dstArrayElement = 0;
			descriptorWrites[5].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			descriptorWrites[5].descriptorCount = static_cast<uint32_t>(imageInfoShadow.size());
			descriptorWrites[5].pImageInfo = imageInfoShadow.data();

			vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
		}
		
		vM->str_VulkanDescriptor->str_descriptorSets = m_descriptorSets;
		Debug::Info("Initialisation du DescriptorSetsManager");
		
		return true;
	}


	void DescriptorSets::Release(VulkanMisc * vM)
	{
		//vkFreeDescriptorSets(vM->str_VulkanDeviceMisc->str_device, vM->str_VulkanDescriptor->str_descriptorPool, static_cast<uint32_t>(m_descriptorSets.size()), m_descriptorSets.data());
		Debug::Info("Liberation du DescriptorSetsManager");
	}
}
