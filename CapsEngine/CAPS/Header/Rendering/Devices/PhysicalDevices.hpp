#ifndef __CAPS_PHYSICAL_DEVICES__
#define __CAPS_PHYSICAL_DEVICES__

#include "ValidationLayer.hpp"
#include "InstanceV.hpp"
#include "WindowSurface.hpp"
//#include "SwapChain.hpp"
#include <set>
#include <stdexcept>
#include <vector>
#include <optional>

namespace Ge
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
		bool isComplete()
		{
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};
	class PhysicalDevices
	{
	public:
		static VkSampleCountFlagBits getMaxUsableSampleCount(VulkanDeviceMisc * vDM);
		static bool isDeviceSuitable(VkPhysicalDevice device, VulkanDeviceMisc * vDM);
		static bool checkDeviceExtensionSupport(VkPhysicalDevice device, VulkanDeviceMisc * vDM);
		static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VulkanDeviceMisc * vDM);
		static std::vector<const char*> getDeviceExtensions();
		static uint32_t getCountQueueFamily(VkPhysicalDevice device);
		static uint32_t getGraphiqueIndexFamily(VkPhysicalDevice device);
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanDeviceMisc * vDM);
		void Release();
	private:
		uint32_t m_deviceCount = 0;
		std::vector<VkPhysicalDevice> m_devices;
		VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
		VkSampleCountFlagBits m_msaaSamples = VK_SAMPLE_COUNT_1_BIT;//multi sampling pour éviter le crénelage
		VkPhysicalDeviceProperties m_physicalDeviceProperties;
		static std::vector<const char*> deviceExtensions;
	};
}

#endif //__CAPS_PHYSICAL_DEVICES__