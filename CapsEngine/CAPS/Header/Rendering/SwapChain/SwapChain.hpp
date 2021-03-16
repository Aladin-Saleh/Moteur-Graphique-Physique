#ifndef __CAPS_SWAP_CHAIN__
#define __CAPS_SWAP_CHAIN__

#include "Debug.hpp"
#include <algorithm>
#include "ImageViews.hpp"
#include "RenderPass.hpp"
#include "DescriptorSetLayout.hpp"
#include "GraphicsPipeline.hpp"

namespace Ge
{
	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;//nombre min/max d'images dans la swap chain, hauteur/largeur min/max des images
		std::vector<VkSurfaceFormatKHR> formats;//Format de la surface (format des pixels, palette de couleur)
		std::vector<VkPresentModeKHR> presentModes;//Mode de présentation disponibles
	};
	class SwapChain
	{
	public:
		static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VulkanDeviceMisc * vDM);// vérifier qu'elle est compatible la surface de fenêtre(Window Surface)
		void ReCreateSwapChain(VulkanMisc * vM);
		void ReCreateDescriptor(VulkanMisc * vM);
	private:
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, VulkanDeviceMisc * vDM);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		bool cSwapChain(VulkanMisc * vM);
		void rSwapChain(VulkanMisc * vM);
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanMisc * vM);
		void Release(VulkanMisc * vM);
		void rcSwapChain(VulkanMisc * vM);
	private:
		VkExtent2D m_swapChainExtent;
		VkFormat m_swapChainImageFormat;
		std::vector<VkImage> m_swapChainImages;
		VkSwapchainKHR m_swapChain;
		ImageViews m_imageViews;
		RenderPass m_renderPass;
		DescriptorSetLayout m_descriptorSetLayout;
		GraphicsPipeline m_graphicsPipeline;
		uint32_t m_imageCount;
	};
}

#endif //__CAPS_SWAP_CHAIN__