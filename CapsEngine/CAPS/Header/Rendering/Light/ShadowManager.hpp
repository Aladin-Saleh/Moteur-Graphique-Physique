#ifndef __CAPS_SHADOW_MANAGER__
#define __CAPS_SHADOW_MANAGER__

#include "VulkanMisc.hpp"
#include "BufferManager.hpp"
#include "GraphicsPipeline.hpp"
#include "MShape.hpp"
#include "Debug.hpp"

#define SHADOWMAP_DIM 2048

namespace Ge
{
	struct FrameBufferAttachment {
		VmaBufferImage mem;
		VkImageView view;
	};
	struct OffscreenPass {
		int32_t width, height;
		VkFramebuffer frameBuffer;
		FrameBufferAttachment depth;
		VkRenderPass renderPass;
		VkSampler depthSampler;
		VkDescriptorImageInfo descriptor;
	};

	class ShadowManager
	{
	private:
		friend class LightManager;
		bool Initialize(VulkanMisc * vM);
		void Release();
	private:
		friend class CommandBuffers;
		void CreateDescriptorPool();
		void BuildCommandBufferShadow(VkCommandBuffer cmdBuffer, std::vector<MShape*> models);
		void UpdateDescriptorShadowMap(std::vector<VkDescriptorBufferInfo> bufferInfolights, std::vector<VkDescriptorBufferInfo> bufferInfoMesh);
		void CreateDescriptorSetLayout(int nblight);
		void CreatePipelineLayout();
		void CreateGraphiquePipeline();
	private:
		friend class DescriptorSets;
		OffscreenPass m_offscreenPass;
		VulkanMisc * vulkanM;
		VkDescriptorSetLayout m_descriptorSetLayout;
		VkPipelineLayout m_pipelineLayout;
		VkPipeline m_offscreenPipeline;
		VkDescriptorPool m_offscreenDescriptorPool = VK_NULL_HANDLE;
		ShaderElement m_vertexShadowShader;
		VkDescriptorSet m_descriptorSet;
		VkDescriptorPoolCreateInfo m_descriptorPoolInfo{};
		float depthBiasConstant = 1.25f;
		float depthBiasSlope = 1.75f;
	};
}

#endif //!__CAPS_SHADOW_MANAGER__