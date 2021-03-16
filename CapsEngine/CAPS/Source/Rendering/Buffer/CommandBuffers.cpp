#include "CommandBuffers.hpp"

namespace Ge
{
	bool CommandBuffers::Initialize(VulkanMisc * vM, Model_Manager * mM, ShadowManager * sM)
	{
		std::vector<VkFramebuffer> swapChainFramebuffers = vM->str_VulkanCommandeBufferMisc->str_swapChainFramebuffers;
		std::vector<MShape*> models = mM->getModels();
		std::vector<VkDescriptorSet> descriptorSets = vM->str_VulkanDescriptor->str_descriptorSets;

		m_commandBuffers.resize( swapChainFramebuffers.size());

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = vM->str_VulkanCommandeBufferMisc->str_commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();

		if (vkAllocateCommandBuffers(vM->str_VulkanDeviceMisc->str_device, &allocInfo, m_commandBuffers.data()) != VK_SUCCESS)
		{
			Debug::Error("Echec de l'allocation du command buffers");
			return false;
		}
		
		for (size_t i = 0; i < m_commandBuffers.size(); i++)
		{
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;			

			if (vkBeginCommandBuffer(m_commandBuffers[i], &beginInfo) != VK_SUCCESS)
			{
				Debug::Error("Echec de l'enregistrer du commande buffer");
				return false;
			}

			sM->BuildCommandBufferShadow(m_commandBuffers[i], models);

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = vM->str_VulkanSwapChainMisc->str_renderPass;
			renderPassInfo.framebuffer = swapChainFramebuffers[i];
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = vM->str_VulkanSwapChainMisc->str_swapChainExtent;

			std::array<VkClearValue, 2> clearValues{};
			clearValues[0].color = { 0.682f, 0.811f, 0.917f, 1.0f };
			clearValues[1].depthStencil = { 1.0f, 0 };
			VkDeviceSize offsets[] = { 0 };

			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(m_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			vkCmdBindPipeline(m_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, vM->str_VulkanSwapChainMisc->str_graphicsPipeline);

			for (MShape * mesh : models)
			{
				mesh->Render(m_commandBuffers[i],vM->str_VulkanDescriptor->str_descriptorSets[i],vM->str_VulkanSwapChainMisc->str_pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT);
			}

			vkCmdEndRenderPass(m_commandBuffers[i]);

			if (vkEndCommandBuffer(m_commandBuffers[i]) != VK_SUCCESS)
			{
				Debug::Error("Echec de l'enregistrer du commande buffer");
				return false;
			}
		}
		vM->str_VulkanCommandeBufferMisc->str_commandBuffers = m_commandBuffers;

		Debug::Info("Initialisation du CommandBuffersManager");
		return true;
	}

	void CommandBuffers::Release(VulkanMisc * vM)
	{
		vkFreeCommandBuffers(vM->str_VulkanDeviceMisc->str_device, vM->str_VulkanCommandeBufferMisc->str_commandPool, static_cast<uint32_t>(m_commandBuffers.size()), m_commandBuffers.data());
		Debug::Info("Liberation du CommandBuffersManager");
	}

	VkCommandBuffer CommandBuffers::beginSingleTimeCommands(VulkanMisc * vM)
	{
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = vM->str_VulkanCommandeBufferMisc->str_commandPool;
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(vM->str_VulkanDeviceMisc->str_device, &allocInfo, &commandBuffer);

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);

		return commandBuffer;
	}

	void CommandBuffers::endSingleTimeCommands(VkCommandBuffer commandBuffer, VulkanMisc * vM)
	{
		VkQueue graphicsQueue = vM->str_VulkanDeviceMisc->str_graphicsQueue;
		vkEndCommandBuffer(commandBuffer);

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(graphicsQueue);

		vkFreeCommandBuffers(vM->str_VulkanDeviceMisc->str_device, vM->str_VulkanCommandeBufferMisc->str_commandPool, 1, &commandBuffer);
	}
}
