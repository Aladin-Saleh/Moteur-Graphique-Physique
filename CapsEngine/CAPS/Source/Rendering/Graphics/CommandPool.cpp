#include "CommandPool.hpp"
#include "PhysicalDevices.hpp"

namespace Ge
{
	bool CommandPool::Initialize(VulkanDeviceMisc * vM, VulkanCommandeBufferMisc * vCM)
	{
		QueueFamilyIndices queueFamilyIndices = PhysicalDevices::findQueueFamilies(vM->str_physicalDevice,vM);

		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

		if (vkCreateCommandPool(vM->str_device, &poolInfo, nullptr, &m_commandPool) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation de la command pool");
			return false;
		}
		vCM->str_commandPool = m_commandPool;
		Debug::Info("Initialisation de la CommandPool");
		return true;
	}

	void CommandPool::Release(VulkanDeviceMisc * vM)
	{
		Debug::Info("Liberation du CommandPool");
		vkDestroyCommandPool(vM->str_device, m_commandPool, nullptr);
	}
}