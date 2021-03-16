#include "ShadowManager.hpp"

namespace Ge
{
	VkBool32 formatIsFilterable(VkPhysicalDevice physicalDevice, VkFormat format, VkImageTiling tiling)
	{
		VkFormatProperties formatProps;
		vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &formatProps);

		if (tiling == VK_IMAGE_TILING_OPTIMAL)
			return formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT;

		if (tiling == VK_IMAGE_TILING_LINEAR)
			return formatProps.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT;

		return false;
	}

	bool ShadowManager::Initialize(VulkanMisc * vM)
	{
		m_offscreenPass.width = SHADOWMAP_DIM;
		m_offscreenPass.height = SHADOWMAP_DIM;

		vulkanM = vM;

		BufferManager::createImageBuffer(
			m_offscreenPass.width,
			m_offscreenPass.height,
			1,
			VK_SAMPLE_COUNT_1_BIT,
			VK_FORMAT_D16_UNORM,
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			m_offscreenPass.depth.mem,
			vM->str_VulkanDeviceMisc
			);

		VkImageViewCreateInfo depthStencilView {};
		depthStencilView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		depthStencilView.viewType = VK_IMAGE_VIEW_TYPE_2D;
		depthStencilView.format = VK_FORMAT_D16_UNORM;
		depthStencilView.subresourceRange = {};
		depthStencilView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
		depthStencilView.subresourceRange.baseMipLevel = 0;
		depthStencilView.subresourceRange.levelCount = 1;
		depthStencilView.subresourceRange.baseArrayLayer = 0;
		depthStencilView.subresourceRange.layerCount = 1;
		depthStencilView.image = m_offscreenPass.depth.mem.image;
		if(vkCreateImageView(vM->str_VulkanDeviceMisc->str_device, &depthStencilView, nullptr, &m_offscreenPass.depth.view) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'une imageView pour la Shadow map");
			return false;
		}

		VkFilter shadowmap_filter = formatIsFilterable(vM->str_VulkanDeviceMisc->str_physicalDevice, VK_FORMAT_D16_UNORM, VK_IMAGE_TILING_OPTIMAL) ? VK_FILTER_LINEAR : VK_FILTER_NEAREST;
		VkSamplerCreateInfo sampler{};
		sampler.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		sampler.maxAnisotropy = 1.0f;
		sampler.magFilter = shadowmap_filter;
		sampler.minFilter = shadowmap_filter;
		sampler.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		sampler.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		sampler.addressModeV = sampler.addressModeU;
		sampler.addressModeW = sampler.addressModeU;
		sampler.mipLodBias = 0.0f;
		sampler.maxAnisotropy = 1.0f;
		sampler.minLod = 0.0f;
		sampler.maxLod = 1.0f;
		sampler.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
		if (vkCreateSampler(vM->str_VulkanDeviceMisc->str_device, &sampler, nullptr, &m_offscreenPass.depthSampler) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'un Sampler pour la Shadow map");
			return false;
		}

		VkAttachmentDescription attachmentDescription{};
		attachmentDescription.format = VK_FORMAT_D16_UNORM;
		attachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
		attachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attachmentDescription.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

		VkAttachmentReference depthReference = {};
		depthReference.attachment = 0;
		depthReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 0;
		subpass.pDepthStencilAttachment = &depthReference;

		std::array<VkSubpassDependency, 2> dependencies;

		dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
		dependencies[0].dstSubpass = 0;
		dependencies[0].srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		dependencies[0].dstStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		dependencies[0].srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
		dependencies[0].dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

		dependencies[1].srcSubpass = 0;
		dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
		dependencies[1].srcStageMask = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
		dependencies[1].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		dependencies[1].srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		dependencies[1].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

		VkRenderPassCreateInfo renderPassCreateInfo{};
		renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassCreateInfo.attachmentCount = 1;
		renderPassCreateInfo.pAttachments = &attachmentDescription;
		renderPassCreateInfo.subpassCount = 1;
		renderPassCreateInfo.pSubpasses = &subpass;
		renderPassCreateInfo.dependencyCount = static_cast<uint32_t>(dependencies.size());
		renderPassCreateInfo.pDependencies = dependencies.data();

		if (vkCreateRenderPass(vM->str_VulkanDeviceMisc->str_device, &renderPassCreateInfo, nullptr, &m_offscreenPass.renderPass) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'un FrameBuffer pour la Shadow map");
			return false;
		}

		VkFramebufferCreateInfo fbufCreateInfo{};
		fbufCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		fbufCreateInfo.renderPass = m_offscreenPass.renderPass;
		fbufCreateInfo.attachmentCount = 1;
		fbufCreateInfo.pAttachments = &m_offscreenPass.depth.view;
		fbufCreateInfo.width = m_offscreenPass.width;
		fbufCreateInfo.height = m_offscreenPass.height;
		fbufCreateInfo.layers = 1;

		if (vkCreateFramebuffer(vM->str_VulkanDeviceMisc->str_device, &fbufCreateInfo, nullptr, &m_offscreenPass.frameBuffer) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'un FrameBuffer pour la Shadow map");
			return false;
		}

		CreateDescriptorSetLayout(1);
		CreatePipelineLayout();

		//create graphique pipeline
		CreateGraphiquePipeline();
		

		CreateDescriptorPool();

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = m_offscreenDescriptorPool;
		allocInfo.pSetLayouts = &m_descriptorSetLayout;
		allocInfo.descriptorSetCount = 1;

		// Offscreen shadow map generation
		if (vkAllocateDescriptorSets(vM->str_VulkanDeviceMisc->str_device, &allocInfo, &m_descriptorSet) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'un descriptorSets pour la Shadow map");
			return false;
		}

		Debug::Info("Initialisation de la shadow map");		
		return true;
	}

	void ShadowManager::CreateDescriptorPool()
	{
		std::vector<VkImage> swapChainImages = vulkanM->str_VulkanSwapChainMisc->str_swapChainImages;
		VkDescriptorPoolSize descriptorPoolSize{};
		descriptorPoolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorPoolSize.descriptorCount = static_cast<uint32_t>(swapChainImages.size());

		VkDescriptorPoolSize descriptorPoolSize1{};
		descriptorPoolSize1.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorPoolSize1.descriptorCount = static_cast<uint32_t>(swapChainImages.size()*(vulkanM->str_VulkanDescriptor->modelCount == 0 ? 1 : vulkanM->str_VulkanDescriptor->modelCount));

		VkDescriptorPoolSize descriptorPoolSize2{};
		descriptorPoolSize2.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptorPoolSize2.descriptorCount = static_cast<uint32_t>(swapChainImages.size());

		std::vector<VkDescriptorPoolSize> poolSizes = { descriptorPoolSize,descriptorPoolSize2,descriptorPoolSize1 };
		m_descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		m_descriptorPoolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
		m_descriptorPoolInfo.pPoolSizes = poolSizes.data();
		m_descriptorPoolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size());

		if (vkCreateDescriptorPool(vulkanM->str_VulkanDeviceMisc->str_device, &m_descriptorPoolInfo, nullptr, &m_offscreenDescriptorPool))
		{
			Debug::Error("Echec de la creation d'un descriptorPool pour la shadow Map");
		}
	}

	void ShadowManager::BuildCommandBufferShadow(VkCommandBuffer cmdBuffer, std::vector<MShape*> models)
	{
		VkCommandBufferBeginInfo cmdBufInfo{};
		cmdBufInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		VkClearValue clearValues[2];
		VkViewport viewport;
		VkRect2D scissor;

		/*
			Première passe de rendu : Générer une carte des ombres en rendant la scène à partir du point de vue de la lumière
		*/

		clearValues[0].depthStencil = { 1.0f, 0 };

		VkRenderPassBeginInfo renderPassBeginInfo{};
		renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassBeginInfo.renderPass = m_offscreenPass.renderPass;
		renderPassBeginInfo.framebuffer = m_offscreenPass.frameBuffer;
		renderPassBeginInfo.renderArea.extent.width = m_offscreenPass.width;
		renderPassBeginInfo.renderArea.extent.height = m_offscreenPass.height;
		renderPassBeginInfo.clearValueCount = 1;
		renderPassBeginInfo.pClearValues = clearValues;

		vkCmdBeginRenderPass(cmdBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

		viewport.width = m_offscreenPass.width;
		viewport.height = m_offscreenPass.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		vkCmdSetViewport(cmdBuffer, 0, 1, &viewport);

		scissor.extent.width = m_offscreenPass.width;
		scissor.extent.height = m_offscreenPass.height;
		scissor.offset.x = 0;
		scissor.offset.y = 0;
		vkCmdSetScissor(cmdBuffer, 0, 1, &scissor);

		vkCmdSetDepthBias(
			cmdBuffer,
			depthBiasConstant,
			0.0f,
			depthBiasSlope);

		vkCmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_offscreenPipeline);
		vkCmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipelineLayout, 0, 1, &m_descriptorSet, 0, nullptr);
		for (int i = 0; i < models.size(); i++)
		{
			models[i]->Render(cmdBuffer, m_descriptorSet, m_pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT);
		}
		vkCmdEndRenderPass(cmdBuffer);

	}

	void ShadowManager::UpdateDescriptorShadowMap(std::vector<VkDescriptorBufferInfo> bufferInfolights, std::vector<VkDescriptorBufferInfo> bufferInfoMesh)
	{
		vkDestroyPipeline(vulkanM->str_VulkanDeviceMisc->str_device, m_offscreenPipeline, nullptr);
		vkDestroyPipelineLayout(vulkanM->str_VulkanDeviceMisc->str_device, m_pipelineLayout, nullptr);
		vkDestroyDescriptorSetLayout(vulkanM->str_VulkanDeviceMisc->str_device, m_descriptorSetLayout, nullptr);
		vkDestroyDescriptorPool(vulkanM->str_VulkanDeviceMisc->str_device, m_offscreenDescriptorPool, nullptr);
		
		CreateDescriptorSetLayout(bufferInfolights.size());
		CreatePipelineLayout();
		CreateGraphiquePipeline();
		CreateDescriptorPool();

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = m_offscreenDescriptorPool;
		allocInfo.pSetLayouts = &m_descriptorSetLayout;
		allocInfo.descriptorSetCount = 1;

		if (vkAllocateDescriptorSets(vulkanM->str_VulkanDeviceMisc->str_device, &allocInfo, &m_descriptorSet) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'un descriptorSets pour la Shadow map");
		}

		std::vector<VkWriteDescriptorSet> writeDescriptorSets;
		VkWriteDescriptorSet writeDescriptorSet{};
		writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writeDescriptorSet.dstSet = m_descriptorSet;
		writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		writeDescriptorSet.dstBinding = 0;
		writeDescriptorSet.pBufferInfo = bufferInfolights.data();
		writeDescriptorSet.descriptorCount = static_cast<uint32_t>(bufferInfolights.size());

		VkWriteDescriptorSet writeDescriptorSetMesh{};
		writeDescriptorSetMesh.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writeDescriptorSetMesh.dstSet = m_descriptorSet;
		writeDescriptorSetMesh.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		writeDescriptorSetMesh.dstBinding = 2;
		writeDescriptorSetMesh.pBufferInfo = bufferInfoMesh.data();
		writeDescriptorSetMesh.descriptorCount = static_cast<uint32_t>(bufferInfoMesh.size());

		writeDescriptorSets = {
			// Binding 0 : Vertex shader uniform buffer
			writeDescriptorSet,
			// Binding 1 : Vertex shader uniform buffer
			writeDescriptorSetMesh
		};
		vkUpdateDescriptorSets(vulkanM->str_VulkanDeviceMisc->str_device, writeDescriptorSets.size(), writeDescriptorSets.data(), 0, nullptr);
	}

	void ShadowManager::CreateDescriptorSetLayout(int nblight)
	{
		VkDescriptorSetLayoutBinding setLayoutBinding{};
		setLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		setLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		setLayoutBinding.binding = 0;
		setLayoutBinding.descriptorCount = nblight;

		VkDescriptorSetLayoutBinding setLayoutBinding1{};
		setLayoutBinding1.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		setLayoutBinding1.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		setLayoutBinding1.binding = 2;
		setLayoutBinding1.descriptorCount = vulkanM->str_VulkanDescriptor->modelCount == 0 ? 1 : vulkanM->str_VulkanDescriptor->modelCount;

		VkDescriptorSetLayoutBinding setLayoutBinding2{};
		setLayoutBinding2.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		setLayoutBinding2.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
		setLayoutBinding2.binding = 1;
		setLayoutBinding2.descriptorCount = 1;

		std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings = {
			// Binding 0 : Vertex shader uniform buffer
			setLayoutBinding,
			// Binding 1  : Fragment shader image sampler (shadow map)
			setLayoutBinding2,
			// Binding 2 : Vertex shader uniform buffer
			setLayoutBinding1
		};
		VkDescriptorSetLayoutCreateInfo descriptorLayout{};
		descriptorLayout.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		descriptorLayout.pBindings = setLayoutBindings.data();
		descriptorLayout.bindingCount = static_cast<uint32_t>(setLayoutBindings.size());
		if (vkCreateDescriptorSetLayout(vulkanM->str_VulkanDeviceMisc->str_device, &descriptorLayout, nullptr, &m_descriptorSetLayout) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'un DescriptorSetLayout pour la Shadow map");
		}
	}

	void ShadowManager::CreatePipelineLayout()
	{
		VkPushConstantRange pushConstantRange{};
		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		pushConstantRange.offset = 0;
		pushConstantRange.size = sizeof(PushConstants);

		VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo{};
		pPipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pPipelineLayoutCreateInfo.setLayoutCount = 1;
		pPipelineLayoutCreateInfo.pSetLayouts = &m_descriptorSetLayout;
		pPipelineLayoutCreateInfo.pPushConstantRanges = &pushConstantRange;
		pPipelineLayoutCreateInfo.pushConstantRangeCount = 1;

		if (vkCreatePipelineLayout(vulkanM->str_VulkanDeviceMisc->str_device, &pPipelineLayoutCreateInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'un PipelineLayout pour la Shadow map");
		}
	}

	void ShadowManager::CreateGraphiquePipeline()
	{
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCI{};
		inputAssemblyStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssemblyStateCI.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssemblyStateCI.flags = 0;
		inputAssemblyStateCI.primitiveRestartEnable = VK_FALSE;
		VkPipelineRasterizationStateCreateInfo rasterizationStateCI{};
		rasterizationStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizationStateCI.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizationStateCI.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizationStateCI.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterizationStateCI.flags = 0;
		rasterizationStateCI.depthClampEnable = VK_FALSE;
		rasterizationStateCI.depthBiasEnable = VK_TRUE;
		rasterizationStateCI.lineWidth = 1.0f;
		VkPipelineColorBlendAttachmentState blendAttachmentState{};
		blendAttachmentState.colorWriteMask = 0xf;
		blendAttachmentState.blendEnable = VK_FALSE;
		VkPipelineColorBlendStateCreateInfo colorBlendStateCI{};
		colorBlendStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlendStateCI.attachmentCount = 0;
		colorBlendStateCI.pAttachments = &blendAttachmentState;
		VkPipelineDepthStencilStateCreateInfo depthStencilStateCI{};
		depthStencilStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencilStateCI.depthTestEnable = VK_TRUE;
		depthStencilStateCI.depthWriteEnable = VK_TRUE;
		depthStencilStateCI.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
		depthStencilStateCI.back.compareOp = VK_COMPARE_OP_ALWAYS;
		VkPipelineViewportStateCreateInfo viewportStateCI{};
		viewportStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportStateCI.viewportCount = 1;
		viewportStateCI.scissorCount = 1;
		viewportStateCI.flags = 0;
		VkPipelineMultisampleStateCreateInfo multisampleStateCI{};
		multisampleStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampleStateCI.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampleStateCI.flags = 0;
		std::vector<VkDynamicState> dynamicStateEnables = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR,VK_DYNAMIC_STATE_DEPTH_BIAS };
		VkPipelineDynamicStateCreateInfo dynamicStateCI{};
		dynamicStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicStateCI.pDynamicStates = dynamicStateEnables.data();
		dynamicStateCI.dynamicStateCount = dynamicStateEnables.size();
		dynamicStateCI.flags = 0;
		std::array<VkPipelineShaderStageCreateInfo, 1> shaderStages;

		VkGraphicsPipelineCreateInfo pipelineCI{};
		pipelineCI.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineCI.layout = m_pipelineLayout;
		pipelineCI.renderPass = m_offscreenPass.renderPass;
		pipelineCI.flags = 0;
		pipelineCI.basePipelineIndex = -1;
		pipelineCI.basePipelineHandle = VK_NULL_HANDLE;
		pipelineCI.pInputAssemblyState = &inputAssemblyStateCI;
		pipelineCI.pRasterizationState = &rasterizationStateCI;
		pipelineCI.pColorBlendState = &colorBlendStateCI;
		pipelineCI.pMultisampleState = &multisampleStateCI;
		pipelineCI.pViewportState = &viewportStateCI;
		pipelineCI.pDepthStencilState = &depthStencilStateCI;
		pipelineCI.pDynamicState = &dynamicStateCI;
		pipelineCI.stageCount = shaderStages.size();
		pipelineCI.pStages = shaderStages.data();

		m_vertexShadowShader = GraphicsPipeline::LoadShader("../Shader/offscreen.vert.spv", "main", vulkanM->str_VulkanDeviceMisc->str_device, true);
		shaderStages[0] = m_vertexShadowShader.shaderStageCreateInfo;

		auto bindingDescription = Vertex::getBindingDescription();//--------------------------------------------------------------------------------------------------------------- FIXE ME
		auto attributeDescriptions = Vertex::getAttributeDescriptions();

		VkPipelineVertexInputStateCreateInfo inputStateVertex{};
		inputStateVertex.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		inputStateVertex.vertexBindingDescriptionCount = 1;
		inputStateVertex.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
		inputStateVertex.pVertexBindingDescriptions = &bindingDescription;
		inputStateVertex.pVertexAttributeDescriptions = attributeDescriptions.data();

		pipelineCI.pVertexInputState = &inputStateVertex;

		if (vkCreateGraphicsPipelines(vulkanM->str_VulkanDeviceMisc->str_device, vulkanM->str_VulkanSwapChainMisc->str_graphicsPipelineCache, 1, &pipelineCI, nullptr, &m_offscreenPipeline) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'un graphique pipeline pour la Shadow map");
		}

		GraphicsPipeline::DestroyShaderElement(vulkanM->str_VulkanDeviceMisc->str_device, m_vertexShadowShader);
	}

	void ShadowManager::Release()
	{
		vkDestroySampler(vulkanM->str_VulkanDeviceMisc->str_device, m_offscreenPass.depthSampler, nullptr);
		vkDestroyImageView(vulkanM->str_VulkanDeviceMisc->str_device, m_offscreenPass.depth.view, nullptr);
		BufferManager::destroyImageBuffer(m_offscreenPass.depth.mem);
		vkDestroyFramebuffer(vulkanM->str_VulkanDeviceMisc->str_device, m_offscreenPass.frameBuffer, nullptr);
		vkDestroyRenderPass(vulkanM->str_VulkanDeviceMisc->str_device, m_offscreenPass.renderPass, nullptr);

		vkDestroyPipeline(vulkanM->str_VulkanDeviceMisc->str_device, m_offscreenPipeline, nullptr);

		vkDestroyPipelineLayout(vulkanM->str_VulkanDeviceMisc->str_device, m_pipelineLayout, nullptr);
		vkDestroyDescriptorSetLayout(vulkanM->str_VulkanDeviceMisc->str_device, m_descriptorSetLayout, nullptr);		
		vkDestroyDescriptorPool(vulkanM->str_VulkanDeviceMisc->str_device, m_offscreenDescriptorPool, nullptr);
		Debug::Info("Liberation de la shadow map");
	}
}