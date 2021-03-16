#include "LogicalDevice.hpp"

namespace Ge
{
	bool LogicalDevice::Initialize(VulkanDeviceMisc * vDM, WindowSurface * m_windowSurface)
	{
		QueueFamilyIndices indices = PhysicalDevices::findQueueFamilies(vDM->str_physicalDevice, vDM);
		
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		float queuePriority = 1.0f;
		for (uint32_t queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{};
		deviceFeatures.samplerAnisotropy = VK_TRUE;
		deviceFeatures.sampleRateShading = VK_TRUE; // Activation du sample shading pour le device

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();

		createInfo.pEnabledFeatures = &deviceFeatures;
		
		std::vector<const char *> deviceExtensions = PhysicalDevices::getDeviceExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceExtensions.data();

		const std::vector<const char*> vLayer = ValidationLayer::getValidationLayers();

		if (ValidationLayer::getEnableValidationLayers())
		{
			
			createInfo.enabledLayerCount = static_cast<uint32_t>(vLayer.size());
			createInfo.ppEnabledLayerNames = vLayer.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		VkPhysicalDeviceDescriptorIndexingFeaturesEXT physicalDeviceDescriptorIndexingFeatures{};
		physicalDeviceDescriptorIndexingFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES_EXT;
		physicalDeviceDescriptorIndexingFeatures.shaderSampledImageArrayNonUniformIndexing = VK_TRUE;
		physicalDeviceDescriptorIndexingFeatures.runtimeDescriptorArray = VK_TRUE;
		physicalDeviceDescriptorIndexingFeatures.descriptorBindingVariableDescriptorCount = VK_TRUE;
		VkPhysicalDeviceFeatures2 physicalDeviceFeatures2{};
		physicalDeviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
		physicalDeviceFeatures2.features = deviceFeatures;
		physicalDeviceFeatures2.pNext = &physicalDeviceDescriptorIndexingFeatures;
		createInfo.pEnabledFeatures = nullptr;
		createInfo.pNext = &physicalDeviceFeatures2;

		if (vkCreateDevice(vDM->str_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS)
		{
			Debug::Error("Echec lors de la creation du Logical Device");
			return false;
		}
		Debug::Info("Initialisation du Logical Device");
		
		vkGetDeviceQueue(m_device, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
		m_windowSurface->SetupPresentQueue(m_device, indices.presentFamily.value(), vDM);
		vDM->str_device = m_device;
		vDM->str_graphicsQueue = m_graphicsQueue;
		return true;
	}

	void LogicalDevice::Release(VulkanDeviceMisc * vDM)
	{		
		vkDestroyDevice(vDM->str_device, nullptr);
		vDM->str_device = VK_NULL_HANDLE;
		Debug::Info("Liberation du Logical Device");
	}
}

