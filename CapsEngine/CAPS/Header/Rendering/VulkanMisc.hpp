#ifndef __CAPS_VULKAN_MISC__
#define __CAPS_VULKAN_MISC__

#include "vulkan/vulkan.h"
//#include "/home/m/Documents/vulkansdk-linux/1.2.148.1/x86_64/include/vulkan/vulkan.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <array>
#include <vector>
#include <stdio.h>          
#include <stdlib.h>  

namespace Ge
{

	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 color;
		glm::vec2 texCoord;

		static VkVertexInputBindingDescription getBindingDescription()
		{
			VkVertexInputBindingDescription bindingDescription{};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions()
		{
			std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);

			attributeDescriptions[2].binding = 0;
			attributeDescriptions[2].location = 2;
			attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

			return attributeDescriptions;
		}

		bool operator==(const Vertex& other) const
		{
			return pos == other.pos && color == other.color && texCoord == other.texCoord;
		}
	};

	struct VulkanDeviceMisc
	{
		GLFWwindow * str_window = nullptr;
		VkInstance str_instance = VK_NULL_HANDLE;
		VkQueue str_presentQueue = VK_NULL_HANDLE;
		VkSurfaceKHR str_surface = VK_NULL_HANDLE;
		VkQueue str_graphicsQueue = VK_NULL_HANDLE;
		VkDevice str_device = VK_NULL_HANDLE;
		VkPhysicalDevice str_physicalDevice = VK_NULL_HANDLE;
		VkSampleCountFlagBits str_msaaSamples = VK_SAMPLE_COUNT_1_BIT;
		VkPhysicalDeviceProperties str_physicalDeviceProperties;
	};
	struct VulkanSwapChainMisc
	{
		VkExtent2D str_swapChainExtent;
		VkFormat str_swapChainImageFormat;
		VkFormat str_depthFormat;
		std::vector<VkImage> str_swapChainImages;
		VkSwapchainKHR str_swapChain;
		std::vector<VkImageView> str_swapChainImageViews;
		VkRenderPass str_renderPass = VK_NULL_HANDLE;
		VkDescriptorSetLayout str_descriptorSetLayout;
		VkPipeline str_graphicsPipeline = VK_NULL_HANDLE;
		VkPipeline str_graphicsPipelineSkybox = VK_NULL_HANDLE;
		VkPipelineCache str_graphicsPipelineCache = VK_NULL_HANDLE;
		VkPipelineLayout str_pipelineLayout = VK_NULL_HANDLE;
		uint32_t str_imageCount;
		VkSurfaceFormatKHR str_surfaceFormatKHR;
		VkPresentModeKHR str_presentModeKHR;
	};
	struct VulkanCommandeBufferMisc
	{
		VkCommandPool str_commandPool = VK_NULL_HANDLE;
		std::vector<VkFramebuffer> str_swapChainFramebuffers;

		std::vector<VkCommandBuffer> str_commandBuffers;
		VkImageView str_colorImageView = VK_NULL_HANDLE;
		VkImage str_colorImage = VK_NULL_HANDLE;
		VkDeviceMemory str_colorImageMemory = VK_NULL_HANDLE;
		VkImageView str_depthImageView = VK_NULL_HANDLE;
		bool str_recreate = false;
	};
	struct VulkanDescriptor
	{
		VkDescriptorPool str_descriptorPool = VK_NULL_HANDLE;
		VkDescriptorPool str_imGUIdescriptorPool = VK_NULL_HANDLE;
		std::vector<VkDescriptorSet> str_descriptorSets;
		int shadowLightIndice = 0;
		int modelCount = 0;
		int TextureCount = 0;
		int materialCount = 0;
		int lightCount = 0;
	};
	struct VulkanSynchronisation
	{
		std::vector<VkSemaphore> str_imageAvailableSemaphores;
		std::vector<VkSemaphore> str_renderFinishedSemaphores;
		std::vector<VkFence> str_inFlightFences;
		std::vector<VkFence> str_imagesInFlight;
		int MAX_FRAMES_IN_FLIGHT = 2;
	};

	struct VulkanMisc
	{
		VulkanDeviceMisc * str_VulkanDeviceMisc;
		VulkanSwapChainMisc * str_VulkanSwapChainMisc;
		VulkanCommandeBufferMisc * str_VulkanCommandeBufferMisc;
		VulkanDescriptor * str_VulkanDescriptor;
		VulkanSynchronisation * str_VulkanSynchronisation;
	
	};


}
#endif //!__CAPS_VULKAN_MISC__