#include "Framebuffers.hpp"

namespace Ge
{
	bool FrameBuffers::Initialize(VulkanMisc * mV)
	{
		std::vector<VkImageView> swapChainImageViews = mV->str_VulkanSwapChainMisc->str_swapChainImageViews;
		VkRenderPass renderPass = mV->str_VulkanSwapChainMisc->str_renderPass;
		VkExtent2D swapChainExtent = mV->str_VulkanSwapChainMisc->str_swapChainExtent;
		VkImageView colorImageView = mV->str_VulkanCommandeBufferMisc->str_colorImageView;
		VkImageView depthImageView = mV->str_VulkanCommandeBufferMisc->str_depthImageView;
		m_swapChainFramebuffers.resize(swapChainImageViews.size());

		for (size_t i = 0; i < swapChainImageViews.size(); i++)
		{
			std::array<VkImageView, 3> attachments = {
				colorImageView,
				depthImageView,
				swapChainImageViews[i]
			};

			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = renderPass;
			framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
			framebufferInfo.pAttachments = attachments.data();
			framebufferInfo.width = swapChainExtent.width;
			framebufferInfo.height = swapChainExtent.height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(mV->str_VulkanDeviceMisc->str_device, &framebufferInfo, nullptr, &m_swapChainFramebuffers[i]) != VK_SUCCESS)
			{
				Debug::Error("Echec de la creation d'un framebuffer");
				return false;
			}
		}
		mV->str_VulkanCommandeBufferMisc->str_swapChainFramebuffers = m_swapChainFramebuffers;
		Debug::Info("Initialisation de la FrameBuffers");
		return true;
	}

	void FrameBuffers::Release(VkDevice device)
	{
		for (auto framebuffer : m_swapChainFramebuffers)
		{
			vkDestroyFramebuffer(device, framebuffer, nullptr);
		}
		Debug::Info("Liberation du FrameBuffers");
	}
}