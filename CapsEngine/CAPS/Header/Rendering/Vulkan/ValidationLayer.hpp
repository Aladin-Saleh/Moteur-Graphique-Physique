#ifndef __CAPS_VALIDATION_LAYER__
#define __CAPS_VALIDATION_LAYER__

#include <vector>
#include "Debug.hpp"
#include "InstanceV.hpp"
#include "vulkan/vulkan.h"
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include "VulkanMisc.hpp"

namespace Ge
{
	class ValidationLayer
	{
	public:
		static const std::vector<const char*> getValidationLayers();
		static bool getEnableValidationLayers();
		static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
		static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
		static bool checkValidationLayerSupport();
		static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
		static std::vector<const char*> getRequiredExtensions();
	private:
		friend class RenderingEngine;
		bool Initialize(VkInstance instance);
		void Release(VkInstance instance);
	private:
		static ValidationLayer * s_pInstance;
		const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
		VkDebugUtilsMessengerEXT m_debugMessenger;
#ifdef NDEBUG
		static const bool enableValidationLayers = false;
#else
		static const bool enableValidationLayers = true;
#define IMGUI_VULKAN_DEBUG_REPORT
#endif
	};
}

#endif //__CAPS_VALIDATION_LAYER__