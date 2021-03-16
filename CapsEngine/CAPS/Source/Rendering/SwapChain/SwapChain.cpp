#include "SwapChain.hpp"
#include "PhysicalDevices.hpp"

namespace Ge
{
	bool SwapChain::Initialize(VulkanMisc * vM)
	{
		if (!cSwapChain(vM))
		{
			return false;
		}
		if (m_imageViews.Initialize(&m_swapChainImages, m_swapChainImageFormat, vM))
		{
			Debug::Info("Initialisation de l'ImageViews");
		}
		if (m_renderPass.Initialize(m_swapChainImageFormat, PhysicalDevices::getMaxUsableSampleCount(vM->str_VulkanDeviceMisc), vM))
		{
			Debug::Info("Initialisation de la RenderPass");
		}
		if (m_descriptorSetLayout.Initialize(vM))
		{
			Debug::Info("Initialisation du descriptorSetLayout");
		}
		if (m_graphicsPipeline.Initialize(vM->str_VulkanSwapChainMisc->str_renderPass, m_swapChainExtent, vM->str_VulkanSwapChainMisc->str_descriptorSetLayout,vM))
		{
			Debug::Info("Initialisation du pipeline graphique");
		}
		return true;
	}

	void SwapChain::Release(VulkanMisc * vM)
	{
		rSwapChain(vM);
	}

	void SwapChain::rcSwapChain(VulkanMisc * vM)
	{
		vkDestroySwapchainKHR(vM->str_VulkanDeviceMisc->str_device, m_swapChain, nullptr);
		m_renderPass.Release(vM->str_VulkanDeviceMisc);
		m_imageViews.Release(vM->str_VulkanDeviceMisc);
		m_descriptorSetLayout.Release(vM->str_VulkanDeviceMisc);
		m_graphicsPipeline.Release(vM->str_VulkanDeviceMisc);
		cSwapChain(vM);
		m_imageViews.Initialize(&m_swapChainImages, m_swapChainImageFormat, vM);
		m_renderPass.Initialize(m_swapChainImageFormat, PhysicalDevices::getMaxUsableSampleCount(vM->str_VulkanDeviceMisc), vM);
		m_descriptorSetLayout.Initialize(vM);
		m_graphicsPipeline.Initialize(vM->str_VulkanSwapChainMisc->str_renderPass, m_swapChainExtent, vM->str_VulkanSwapChainMisc->str_descriptorSetLayout, vM);
	}

	VkSurfaceFormatKHR SwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& availableFormat : availableFormats)
		{
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				//VK_FORMAT_B8G8R8A8_SRGB  :  stock les canaux de couleur R, G, B et A dans cet ordre et en entiers non signés de 8 bits.
				//VK_COLOR_SPACE_SRGB_NONLINEAR_KHR si le sRGB est supporté
				return availableFormat;
			}
		}
		return availableFormats[0];
	}

	bool SwapChain::cSwapChain(VulkanMisc * vM)
	{
		VkPhysicalDevice physicalDevice = vM->str_VulkanDeviceMisc->str_physicalDevice;//On recupere le PhysicalDevices
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice, vM->str_VulkanDeviceMisc);//les details de la swapChain du physical Device
		VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);//On veut un format VK_FORMAT_B8G8R8A8_SRGB et un colorSpace VK_COLOR_SPACE_SRGB_NONLINEAR_KHR pour faire le rendu
		VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);//Mode de predentation possible de la swapChain VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_FIFO_KHR,VK_PRESENT_MODE_FIFO_RELAXED_KHR,VK_PRESENT_MODE_MAILBOX_KHR,VK_PRESENT_MODE_FIFO_KHR
		VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities, vM->str_VulkanDeviceMisc);//la taille du buffer

		m_imageCount = swapChainSupport.capabilities.minImageCount + 1;//Normalement on devrait un triple buffering
		if (swapChainSupport.capabilities.maxImageCount > 0 && m_imageCount > swapChainSupport.capabilities.maxImageCount)
		{
			m_imageCount = swapChainSupport.capabilities.maxImageCount;
		}
		VkSurfaceKHR surfaceKHRW = vM->str_VulkanDeviceMisc->str_surface;
		VkSwapchainCreateInfoKHR createInfo{};// cration de la structure de donner pour la cration d'un SwapchainKHR
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = surfaceKHRW;

		createInfo.minImageCount = m_imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;//imageArrayLayers indique le nombre de couches que chaque image possède
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = PhysicalDevices::findQueueFamilies(vM->str_VulkanDeviceMisc->str_physicalDevice, vM->str_VulkanDeviceMisc);
		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		if (indices.graphicsFamily != indices.presentFamily)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;//supr
		VkDevice device = vM->str_VulkanDeviceMisc->str_device;
		if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &m_swapChain) != VK_SUCCESS)
		{
			Debug::Error("vkCreateSwapchainKHR n'a pas reussi a creer une chaine d'echange d'image.");
			return false;
		}

		vkGetSwapchainImagesKHR(device, m_swapChain, &m_imageCount, nullptr);//on recupere le nombre d'image de la swapChain
		m_swapChainImages.resize(m_imageCount);
		vkGetSwapchainImagesKHR(device, m_swapChain, &m_imageCount, m_swapChainImages.data());

		Debug::Info("Initialisation de la SwapChain");
		m_swapChainImageFormat = surfaceFormat.format;
		m_swapChainExtent = extent;
		vM->str_VulkanSwapChainMisc->str_presentModeKHR = presentMode;
		vM->str_VulkanSwapChainMisc->str_surfaceFormatKHR = surfaceFormat;
		vM->str_VulkanSwapChainMisc->str_swapChainExtent = m_swapChainExtent;
		vM->str_VulkanSwapChainMisc->str_swapChainImageFormat = m_swapChainImageFormat;
		vM->str_VulkanSwapChainMisc->str_swapChainImages = m_swapChainImages;
		vM->str_VulkanSwapChainMisc->str_swapChain = m_swapChain;
		vM->str_VulkanSwapChainMisc->str_imageCount = m_imageCount;
		return true;
	}

	void SwapChain::rSwapChain(VulkanMisc * vM)
	{
		m_graphicsPipeline.Release(vM->str_VulkanDeviceMisc);
		Debug::Info("Liberation du pipeline graphique");
		m_descriptorSetLayout.Release(vM->str_VulkanDeviceMisc);
		Debug::Info("Liberation du descriptorSetLayout");
		m_renderPass.Release(vM->str_VulkanDeviceMisc);
		Debug::Info("Liberation de la RenderPass");
		m_imageViews.Release(vM->str_VulkanDeviceMisc);
		Debug::Info("Liberation de l'ImageViews");
		vkDestroySwapchainKHR(vM->str_VulkanDeviceMisc->str_device, m_swapChain, nullptr);
		Debug::Info("Liberation de la SwapChain");
	}

	VkPresentModeKHR SwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		for (const auto& availablePresentMode : availablePresentModes)
		{
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)// Au lieu de bloquer l'application quand le file d'attente est pleine, les images présentes dans la queue sont simplement remplacées par de nouvelles. Ce mode peut être utilisé pour implémenter le triple buffering, qui permet d'éliminer le tearing tout en réduisant le temps de latence entre le rendu et l'affichage qu'une file d'attente implique.
			{
				return availablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;//si l'application est en retard et que la queue est vide pendant le vertical blank. Au lieu d'attendre le prochain vertical blank, une image arrivant dans la file d'attente sera immédiatement transmise à l'écran.
	}

	VkExtent2D SwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, VulkanDeviceMisc * vDM)
	{
		if (capabilities.currentExtent.width != UINT32_MAX)
		{
			return capabilities.currentExtent;
		}
		else
		{
			int width, height;
			glfwGetFramebufferSize(vDM->str_window, &width, &height);

			VkExtent2D actualExtent = {
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};

			actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
			actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

			return actualExtent;
		}
	}

	SwapChainSupportDetails SwapChain::querySwapChainSupport(VkPhysicalDevice device, VulkanDeviceMisc * vDM)
	{
		SwapChainSupportDetails details; // detail de la swap chain structure
		VkSurfaceKHR surface = vDM->str_surface;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);// on recupere les infos depuis le physical device donc la carte graphique

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);// on recupere le nombre de format 

		if (formatCount != 0)// il est possible quil est plusieur format d'affichage disponible
		{
			details.formats.resize(formatCount);//on attribut le nombre de format pour le vector
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data()); // on recupere les formats dans la structure
		}

		uint32_t presentModeCount;// idem avec les modes de presentation
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);// on recup le nombre de mode

		if (presentModeCount != 0)// si il y en a on les attributs
		{
			details.presentModes.resize(presentModeCount);//on attribut le nombre de format pour le vector
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());// on lui ajoute le nombre de presentation
		}

		return details;// return la structure
	}

	void SwapChain::ReCreateSwapChain(VulkanMisc * vM)
	{
		rSwapChain(vM);
		cSwapChain(vM);
	}

	void SwapChain::ReCreateDescriptor(VulkanMisc * vM)
	{
		m_graphicsPipeline.Release(vM->str_VulkanDeviceMisc);
		m_descriptorSetLayout.Release(vM->str_VulkanDeviceMisc);
		m_descriptorSetLayout.Initialize(vM);
		m_graphicsPipeline.Initialize(vM->str_VulkanSwapChainMisc->str_renderPass, m_swapChainExtent, vM->str_VulkanSwapChainMisc->str_descriptorSetLayout, vM);
		Debug::Info("Recreate descriptorSetLayout");
	}
}