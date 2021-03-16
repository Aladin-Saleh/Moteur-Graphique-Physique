#include "PhysicalDevices.hpp"
#include "SwapChain.hpp"

namespace Ge
{
	std::vector<const char*> PhysicalDevices::deviceExtensions =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
	bool PhysicalDevices::Initialize(VulkanDeviceMisc * vDM)
	{
		uint32_t deviceCount = 0; 
		vkEnumeratePhysicalDevices(vDM->str_instance, &deviceCount, nullptr);//On recupere le nombre de cartes graphique de l'appareil

		if (deviceCount == 0)
		{
			Debug::Error("Vulkan n'a pas r�ussi � trouver de carte graphique qui support l'api Vulkan");
			return false;
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);// creation d'un vector de la taille du nombre de carte graphique
		vkEnumeratePhysicalDevices(vDM->str_instance, &deviceCount, devices.data());//recupere toutes les cartes graphiques

		m_physicalDevice = VK_NULL_HANDLE;

		for (int i = 0; i < devices.size() && m_physicalDevice == VK_NULL_HANDLE; i++)// iteration de toutes les cartes graphiques en selectionnant la meilleur
		{
			if (isDeviceSuitable(devices[i], vDM))// verification des conditions d'utilisation de la carte graphique
			{
				m_physicalDevice = devices[i];
				vDM->str_physicalDevice = m_physicalDevice;
				m_msaaSamples = getMaxUsableSampleCount(vDM);// recuperation du nombre maximal de sample par pixel (anti aliasing)
				vDM->str_msaaSamples = m_msaaSamples;
			}
		}

		if (m_physicalDevice == VK_NULL_HANDLE)
		{
			Debug::Error("Vulkan n'a pas reussi a trouver une carte graphique");
			return false;
		}
		Debug::Info("Initialisation du PhysicalDevices");
		vkGetPhysicalDeviceProperties(m_physicalDevice, &m_physicalDeviceProperties);
		vDM->str_physicalDeviceProperties = m_physicalDeviceProperties;
		Debug::Info("Nom de l'appareil: %s",m_physicalDeviceProperties.deviceName);
		return true;
	}

	void PhysicalDevices::Release()
	{
		Debug::Info("Liberation du PhysicalDevices");
	}

	VkSampleCountFlagBits PhysicalDevices::getMaxUsableSampleCount(VulkanDeviceMisc * vDM)
	{
		VkPhysicalDeviceProperties physicalDeviceProperties;// propri�t� de la carte Graphique
		vkGetPhysicalDeviceProperties(vDM->str_physicalDevice, &physicalDeviceProperties);// On recupere les propri�t� de la carte Graphique

		VkSampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts & physicalDeviceProperties.limits.framebufferDepthSampleCounts;// on recupere sont �chantillonage maximal valeur recommander par le constructeur de la carte graphique
		if (counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
		if (counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
		if (counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
		if (counts & VK_SAMPLE_COUNT_8_BIT) { return VK_SAMPLE_COUNT_8_BIT; }
		if (counts & VK_SAMPLE_COUNT_4_BIT) { return VK_SAMPLE_COUNT_4_BIT; }
		if (counts & VK_SAMPLE_COUNT_2_BIT) { return VK_SAMPLE_COUNT_2_BIT; }

		return VK_SAMPLE_COUNT_1_BIT;//si aucune valeur n'est trouver alors l'echantillonage vaut 1
	}

	bool PhysicalDevices::isDeviceSuitable(VkPhysicalDevice device, VulkanDeviceMisc * vDM)
	{
		QueueFamilyIndices indices = PhysicalDevices::findQueueFamilies(device,vDM);//On recupere la famille de queue de la carte graphique Prensent,graphique

		bool extensionsSupported = checkDeviceExtensionSupport(device, vDM);//on regarde si l'extention vulkan est supporter par la carte graphique

		bool swapChainAdequate = false;
		if (extensionsSupported)
		{
			SwapChainSupportDetails swapChainSupport = SwapChain::querySwapChainSupport(device, vDM);//On regarde si la carte graphique possede 
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();//Si les vecteurs sont vides c'est que la carte graphique na pas une configuration adequate pour faire un rendu
		}

		VkPhysicalDeviceFeatures supportedFeatures;
		vkGetPhysicalDeviceFeatures(device, &supportedFeatures);
		return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
	}

	bool PhysicalDevices::checkDeviceExtensionSupport(VkPhysicalDevice device, VulkanDeviceMisc * vDM)
	{
		uint32_t extensionCount;// nombre d'extension suporter
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);// on recupere le nombre d'extention

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);// on cree un vector pour le nombre d'extention
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
		std::vector<const char *> deviceExtensions = PhysicalDevices::deviceExtensions;
		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

		for (const auto& extension : availableExtensions)
		{
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();
	}

	QueueFamilyIndices PhysicalDevices::findQueueFamilies(VkPhysicalDevice device, VulkanDeviceMisc * vDM)
	{
		QueueFamilyIndices indices; // structure du physical device 

		uint32_t queueFamilyCount = 0;//nombre de queue disponible
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);//recupere le nombre de queue

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		for (int i = 0; i < queueFamilies.size() && !indices.isComplete(); i++)
		{
			if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = i;
			}
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, vDM->str_surface, &presentSupport);

			if (presentSupport)
			{
				indices.presentFamily = i;
			}
		}
		return indices;
	}
	
	uint32_t PhysicalDevices::getGraphiqueIndexFamily(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;
		uint32_t queueFamilyCount = 0;//nombre de queue disponible
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);//recupere le nombre de queue

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		for (int i = 0; i < queueFamilies.size() && !indices.isComplete(); i++)
		{
			if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				return i;
			}
		}
		return -1;
	}

	std::vector<const char*> PhysicalDevices::getDeviceExtensions()
	{
		return PhysicalDevices::deviceExtensions;
	}

	uint32_t PhysicalDevices::getCountQueueFamily(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices; // structure du physical device 

		uint32_t queueFamilyCount = 0;//nombre de queue disponible
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);//recupere le nombre de queue

		return queueFamilyCount;
	}
}