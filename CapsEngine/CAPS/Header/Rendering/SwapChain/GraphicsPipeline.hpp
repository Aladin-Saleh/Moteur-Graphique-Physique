#ifndef __CAPS_GAPHICS_PIPELINE__
#define __CAPS_GAPHICS_PIPELINE__

#include "vulkan/vulkan.h"
#include "Debug.hpp"
#include <fstream>
#include <array>
#include "VulkanMisc.hpp"

namespace Ge
{
	struct ShaderElement
	{
		VkShaderModule shaderModule;
		VkPipelineShaderStageCreateInfo shaderStageCreateInfo;
	};
	class GraphicsPipeline
	{
	public:
		static ShaderElement LoadShader(const std::string & filename, const char * entry, VkDevice device,bool isVertex);
		static void DestroyShaderElement(VkDevice device, ShaderElement se);
	private:
		static std::vector<char> readFile(const std::string& filename);
		static VkShaderModule createShaderModule(const std::vector<char>& code, VkDevice device);
	private:
		friend class SwapChain;
		bool Initialize(VkRenderPass renderPass, VkExtent2D swapChainExtent, VkDescriptorSetLayout descriptorSetLayout, VulkanMisc * vM);
		void Release(VulkanDeviceMisc * vM);
	private:
		VkPipeline m_graphicsPipeline;		
		VkPipelineCache m_graphicsPipelineCache;
		VkPipelineLayout m_pipelineLayout;
	};
}

#endif//!__CAPS_GAPHICS_PIPELINE__