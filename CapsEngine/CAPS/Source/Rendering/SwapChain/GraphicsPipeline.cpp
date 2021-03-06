#include "GraphicsPipeline.hpp"
#include "MShape.hpp"

namespace Ge
{

	bool GraphicsPipeline::Initialize(VkRenderPass renderPass, VkExtent2D swapChainExtent, VkDescriptorSetLayout descriptorSetLayout, VulkanMisc * vM)
	{
		ShaderElement VertShader = LoadShader("../Shader/vert.spv", "main", vM->str_VulkanDeviceMisc->str_device, true);
		ShaderElement FragShader = LoadShader("../Shader/frag.spv", "main", vM->str_VulkanDeviceMisc->str_device, false);
		std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages;
		shaderStages[0] = VertShader.shaderStageCreateInfo;
		shaderStages[1] = FragShader.shaderStageCreateInfo;

		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		auto bindingDescription = Vertex::getBindingDescription();
		auto attributeDescriptions = Vertex::getAttributeDescriptions();

		vertexInputInfo.vertexBindingDescriptionCount = 1;
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
		vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

		VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)swapChainExtent.width;
		viewport.height = (float)swapChainExtent.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = swapChainExtent;

		VkPipelineViewportStateCreateInfo viewportState{};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;

		VkPipelineRasterizationStateCreateInfo rasterizer{};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;// VK_POLYGON_MODE_FILL; VK_POLYGON_MODE_LINE;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;

		VkPipelineMultisampleStateCreateInfo multisampling{};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_TRUE; // Activation du sample shading dans la pipeline
		multisampling.rasterizationSamples = vM->str_VulkanDeviceMisc->str_msaaSamples;
		multisampling.minSampleShading = .2f; // Fraction minimale pour le sample shading; plus proche de 1 lisse d'autant plus

		VkPipelineDepthStencilStateCreateInfo depthStencil{};
		depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencil.depthTestEnable = VK_TRUE;
		depthStencil.depthWriteEnable = VK_TRUE;
		depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
		depthStencil.depthBoundsTestEnable = VK_FALSE;
		depthStencil.stencilTestEnable = VK_FALSE;

		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE;

		VkPipelineColorBlendStateCreateInfo colorBlending{};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		VkPushConstantRange pushConstantRange{};
		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		pushConstantRange.offset = 0;
		pushConstantRange.size = sizeof(PushConstants);
	
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 1;
		pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
		pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
		pipelineLayoutInfo.pushConstantRangeCount = 1;
		
		if (vkCreatePipelineLayout(vM->str_VulkanDeviceMisc->str_device, &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'un pipeline layout");
			return false;
		}

		VkPipelineCacheCreateInfo cacheInfo{};
		cacheInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
		cacheInfo.pNext = NULL;
		cacheInfo.flags = 0;
		cacheInfo.initialDataSize = 0;
		cacheInfo.pInitialData = nullptr;

		if (vkCreatePipelineCache(vM->str_VulkanDeviceMisc->str_device, &cacheInfo, nullptr, &m_graphicsPipelineCache) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'un cache pour le pipeline");
			return false;
		}

		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = shaderStages.size();
		pipelineInfo.pStages = shaderStages.data();
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = &depthStencil;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.layout = m_pipelineLayout;
		pipelineInfo.renderPass = renderPass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		if (vkCreateGraphicsPipelines(vM->str_VulkanDeviceMisc->str_device, m_graphicsPipelineCache, 1, &pipelineInfo, nullptr, &m_graphicsPipeline) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation du pipeline graphique");
			return false;
		}

		/*VkPhysicalDevicePipelineCreationCacheControlFeaturesEXT devicePipelineCreationCacheControlFeaturesEXT{};
		devicePipelineCreationCacheControlFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_CREATION_CACHE_CONTROL_FEATURES_EXT;
		devicePipelineCreationCacheControlFeaturesEXT.pNext = nullptr;
		devicePipelineCreationCacheControlFeaturesEXT.pipelineCreationCacheControl = VK_TRUE;*/
	
		DestroyShaderElement(vM->str_VulkanDeviceMisc->str_device, VertShader);
		DestroyShaderElement(vM->str_VulkanDeviceMisc->str_device, FragShader);
		vM->str_VulkanSwapChainMisc->str_graphicsPipeline = m_graphicsPipeline;
		vM->str_VulkanSwapChainMisc->str_graphicsPipelineCache = m_graphicsPipelineCache;
		vM->str_VulkanSwapChainMisc->str_pipelineLayout = m_pipelineLayout;
		return true;
	}

	void GraphicsPipeline::Release(VulkanDeviceMisc * vM)
	{
		
		vkDestroyPipelineCache(vM->str_device, m_graphicsPipelineCache, nullptr);
		vkDestroyPipeline(vM->str_device, m_graphicsPipeline, nullptr);		
		vkDestroyPipelineLayout(vM->str_device, m_pipelineLayout, nullptr);
	} 

	ShaderElement GraphicsPipeline::LoadShader(const std::string & filename, const char * entry, VkDevice device, bool isVertex)
	{
		ShaderElement se;
		auto ShaderCode = readFile(filename);
		VkShaderModule ShaderModule = createShaderModule(ShaderCode, device);

		VkPipelineShaderStageCreateInfo ShaderStageInfo{};
		ShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStageInfo.stage = isVertex ? VK_SHADER_STAGE_VERTEX_BIT : VK_SHADER_STAGE_FRAGMENT_BIT;
		ShaderStageInfo.module = ShaderModule;
		ShaderStageInfo.pName = entry;

		se.shaderModule = ShaderModule;
		se.shaderStageCreateInfo = ShaderStageInfo;
		return se;
	}

	void GraphicsPipeline::DestroyShaderElement(VkDevice device, ShaderElement se)
	{
		vkDestroyShaderModule(device, se.shaderModule, nullptr);
	}

	std::vector<char> GraphicsPipeline::readFile(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (!file.is_open())
		{
			Debug::Error("Echec de l'ouverture du fichier %s",nullptr, filename.c_str());
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}

	VkShaderModule GraphicsPipeline::createShaderModule(const std::vector<char>& code,VkDevice device)
	{
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		VkShaderModule shaderModule;
		if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'un shader module");
		}

		return shaderModule;
	}
}