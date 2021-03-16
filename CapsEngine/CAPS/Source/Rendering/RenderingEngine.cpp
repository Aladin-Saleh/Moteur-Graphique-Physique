#include "RenderingEngine.hpp"

namespace Ge
{
	VulkanMisc * RenderingEngine::Initialize(ptrF * ptrf, SoundEngine * se, PhysicsEngine * pe)
	{
		m_vulkanMisc.str_VulkanCommandeBufferMisc = &m_VulkanCommandeBufferMisc;
		m_vulkanMisc.str_VulkanDescriptor = &m_VulkanDescriptor;
		m_vulkanMisc.str_VulkanDeviceMisc = &m_VulkanDeviceMisc;
		m_vulkanMisc.str_VulkanSwapChainMisc = &m_VulkanSwapChainMisc;
		m_vulkanMisc.str_VulkanSynchronisation = &m_VulkanSynchronisation;

		Debug::Info("Initialisation du moteur de rendu");
		if (!RenderingEngine::m_window.InitWindow(ptrf->Setting->GetWindowWidth(), ptrf->Setting->GetWindowHeight(), ptrf->Setting->GetName(), &m_VulkanDeviceMisc))
		{
			Debug::Error("Erreur d'initialisation de la fenetre");
			return nullptr;
		}
		if (!RenderingEngine::m_instanceV.InitInstance(ptrf->Setting->GetName(), ptrf->Setting->GetVersion(), &m_VulkanDeviceMisc))
		{
			Debug::Error("Erreur d'initialisation de l'instance vulkan");
			return nullptr;
		}
		if (!RenderingEngine::m_validationLayer.Initialize(m_VulkanDeviceMisc.str_instance))
		{
			Debug::Error("Erreur d'initialisation du validation layer de vulkan");
			return nullptr;
		}
		if (!RenderingEngine::m_windowSurface.Initialize(&m_VulkanDeviceMisc))
		{
			Debug::Error("Erreur d'initialisation de la WindowSurface");
			return nullptr;
		}
		if (!RenderingEngine::m_physicalDevice.Initialize(&m_VulkanDeviceMisc))
		{
			Debug::Error("Erreur d'initialisation du Physical Device");
			return nullptr;
		}
		if (!RenderingEngine::m_logicalDevice.Initialize(&m_VulkanDeviceMisc, &m_windowSurface))
		{
			Debug::Error("Erreur d'initialisation du Logical Device");
			return nullptr;
		}
		if (!RenderingEngine::m_bufferManager.Initialize(&m_vulkanMisc))
		{
			Debug::Error("Erreur d'initialisation du Logical Device");
			return nullptr;
		}
		if (!RenderingEngine::m_swapChain.Initialize(&m_vulkanMisc))
		{
			Debug::Error("Erreur d'initialisation de la SwapChain");
			return nullptr;
		}
		if (!RenderingEngine::m_commandPool.Initialize(&m_VulkanDeviceMisc,&m_VulkanCommandeBufferMisc))
		{
			Debug::Error("Erreur d'initialisation de la commandPool");
			return nullptr;
		}
		if (!RenderingEngine::m_colorResources.Initialize(&m_vulkanMisc))
		{
			Debug::Error("Erreur d'initialisation de la colorResources");
			return nullptr;
		}
		if (!RenderingEngine::m_depthResources.Initialize(&m_vulkanMisc))
		{
			Debug::Error("Erreur d'initialisation de la depthResources");
			return nullptr;
		}
		if (!RenderingEngine::m_frameBuffers.Initialize(&m_vulkanMisc))
		{
			Debug::Error("Erreur d'initialisation du framebuffer");
			return nullptr;
		}
		if (!RenderingEngine::m_textureManager.Intialize(&m_vulkanMisc))
		{			
			Debug::Error("Erreur d'initialisation du textureManager");
			return nullptr;
		}
		if (!RenderingEngine::m_modelLoader.Initialize(&m_vulkanMisc))
		{
			Debug::Error("Erreur d'initialisation de la ModelLoader");
			return nullptr;
		}
		if (!RenderingEngine::m_shaderUBdiver.Initialize(&m_vulkanMisc, &m_cameraManager, ptrf->Setting))
		{
			Debug::Error("Erreur d'initialisation de l'ubd");
			return nullptr;
		}
		if (!RenderingEngine::m_materialManager.Initialize(&m_vulkanMisc))
		{
			Debug::Error("Erreur d'initialisation du Material Manager");
			return nullptr;
		}
		if (!RenderingEngine::m_lightManager.Initialize(&m_vulkanMisc))
		{
			Debug::Error("Erreur d'initialisation du light Manager");
			return nullptr;
		}
		if (!RenderingEngine::m_descriptorPool.Initialize(&m_vulkanMisc) || !RenderingEngine::m_descriptorPool.InitializeImGuiPool(&m_vulkanMisc))
		{
			Debug::Error("Erreur d'initialisation du descriptorPool");
			return nullptr;
		}
		if (!RenderingEngine::m_descriptorSets.Initialize(&m_vulkanMisc,&m_modelLoader,&m_textureManager,&m_materialManager,&m_lightManager,&m_shaderUBdiver, m_lightManager.GetShadowManager()))
		{
			Debug::Error("Erreur d'initialisation de la UniformBuffersManager");
			return nullptr;
		}

		if (!RenderingEngine::m_commandBuffers.Initialize(&m_vulkanMisc,&m_modelLoader, m_lightManager.GetShadowManager()))
		{
			Debug::Error("Erreur d'initialisation du CommandBuffers");
			return nullptr;
		}
		if (!RenderingEngine::m_syncObjects.Initialize(&m_vulkanMisc))
		{
			Debug::Error("Erreur d'initialisation du syncObjects");
			return nullptr;
		}
		if (!RenderingEngine::m_HUD.Init_HUD(&m_vulkanMisc,&m_modelLoader,&m_lightManager,pe, se, &m_cameraManager))
		{
			Debug::Error("Erreur d'initialisation de l'HUD");
			return nullptr;
		}
		RenderingEngine::m_cameraManager.Initialize(&m_VulkanSwapChainMisc, ptrf->InputManager);
		ptrf->Camera = &m_cameraManager;
		ptrf->ModelManager = &m_modelLoader;
		ptrf->RayCast = m_modelLoader.getRayCast();
		ptrf->TextureManager = &m_textureManager;
		ptrf->MaterialManager = &m_materialManager;
		ptrf->LightManager = &m_lightManager;
		ptrf->ui = &m_HUD;
		m_ptrf = ptrf;
		return &m_vulkanMisc;
	}

	void RenderingEngine::Release()
	{	
		vkDeviceWaitIdle(m_VulkanDeviceMisc.str_device);
		RenderingEngine::m_cameraManager.Release();
		RenderingEngine::m_HUD.ReleaseHUD(m_VulkanDeviceMisc.str_device);
		RenderingEngine::m_syncObjects.Release(m_VulkanDeviceMisc.str_device);
		RenderingEngine::m_commandBuffers.Release(&m_vulkanMisc);
		RenderingEngine::m_descriptorSets.Release(&m_vulkanMisc);
		RenderingEngine::m_descriptorPool.ReleaseImGuiPool(m_VulkanDeviceMisc.str_device);
		RenderingEngine::m_descriptorPool.Release(m_VulkanDeviceMisc.str_device);
		RenderingEngine::m_lightManager.Release();
		RenderingEngine::m_materialManager.Release();
		RenderingEngine::m_shaderUBdiver.Release();
		RenderingEngine::m_modelLoader.Release(m_VulkanDeviceMisc.str_device);
		RenderingEngine::m_textureManager.Release();
		RenderingEngine::m_depthResources.Release(m_VulkanDeviceMisc.str_device);
		RenderingEngine::m_colorResources.Release(m_VulkanDeviceMisc.str_device);
		RenderingEngine::m_frameBuffers.Release(m_VulkanDeviceMisc.str_device);
		RenderingEngine::m_commandPool.Release(&m_VulkanDeviceMisc);
		RenderingEngine::m_swapChain.Release(&m_vulkanMisc);
		RenderingEngine::m_bufferManager.Release();
		RenderingEngine::m_logicalDevice.Release(&m_VulkanDeviceMisc);
		RenderingEngine::m_physicalDevice.Release();
		RenderingEngine::m_windowSurface.Release(&m_VulkanDeviceMisc);
		RenderingEngine::m_validationLayer.Release(m_VulkanDeviceMisc.str_instance);
		RenderingEngine::m_instanceV.Release();
		RenderingEngine::m_window.Release();
		Debug::Info("Liberation du moteur de rendu");
	}

	ConsoleDebug * RenderingEngine::getConsoleDebug()
	{
		return m_HUD.getConsoleDebug();
	}

	void RenderingEngine::DrawFrame()
	{
		vkWaitForFences(m_VulkanDeviceMisc.str_device, 1, &m_syncObjects.m_inFlightFences[m_currentFrame], VK_TRUE, UINT64_MAX);

		if (m_modelLoader.recreateDescripteurModels() || m_textureManager.recreateDescripteurTextures() || m_materialManager.recreateDescripteurMaterial())
		{
			RenderingEngine::RecreateDescriptorModel();
			m_VulkanCommandeBufferMisc.str_recreate = false;
		}
		if (m_VulkanCommandeBufferMisc.str_recreate)
		{
			vkDeviceWaitIdle(m_VulkanDeviceMisc.str_device);
			RenderingEngine::m_commandBuffers.Release(&m_vulkanMisc);
			RenderingEngine::m_commandBuffers.Initialize(&m_vulkanMisc, &m_modelLoader, m_lightManager.GetShadowManager());
			m_VulkanCommandeBufferMisc.str_recreate = false;
		}

		uint32_t imageIndex;
		
		VkResult result = vkAcquireNextImageKHR(m_VulkanDeviceMisc.str_device, m_VulkanSwapChainMisc.str_swapChain, UINT64_MAX, m_syncObjects.m_imageAvailableSemaphores[m_currentFrame], VK_NULL_HANDLE, &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			RecreateSwapChain();			
			return;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		{
			Debug::Error("Echec l'or de l'optention d'une image de la swap chain");
		}

		

		m_cameraManager.UpdateFlyCamera();
		m_modelLoader.UpdateUniformBufferObject(m_cameraManager.getbaseCam());// metre a jour seulement les buffers qui on besoin d'etre mis a jour (a faire)
		m_materialManager.UpdateUniformBufferObject();
		m_shaderUBdiver.UpdateUniformBufferDiver();
		m_lightManager.UpdateUniformBufferLight();
		if (m_syncObjects.m_imagesInFlight[imageIndex] != VK_NULL_HANDLE)
		{
			vkWaitForFences(m_VulkanDeviceMisc.str_device, 1, &m_syncObjects.m_imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
		}
		m_syncObjects.m_imagesInFlight[imageIndex] = m_syncObjects.m_inFlightFences[m_currentFrame];

		m_HUD.Render(&m_vulkanMisc, imageIndex);

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[] = { m_syncObjects.m_imageAvailableSemaphores[m_currentFrame] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		std::array<VkCommandBuffer, 2> submitCommandBuffers =
		{ m_VulkanCommandeBufferMisc.str_commandBuffers[imageIndex], m_HUD.m_imGuiCommandBuffers[imageIndex] };

		submitInfo.commandBufferCount = static_cast<uint32_t>(submitCommandBuffers.size());
		submitInfo.pCommandBuffers = submitCommandBuffers.data();

		VkSemaphore signalSemaphores[] = { m_VulkanSynchronisation.str_renderFinishedSemaphores[m_currentFrame] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;


		vkResetFences(m_VulkanDeviceMisc.str_device, 1, &m_syncObjects.m_inFlightFences[m_currentFrame]);

		if (vkQueueSubmit(m_VulkanDeviceMisc.str_graphicsQueue, 1, &submitInfo, m_syncObjects.m_inFlightFences[m_currentFrame]) != VK_SUCCESS)
		{
			Debug::Error("Echec l'or de la soumission au command buffer");
		}

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR swapChains[] = { m_VulkanSwapChainMisc.str_swapChain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;

		presentInfo.pImageIndices = &imageIndex;

		result = vkQueuePresentKHR(m_windowSurface.m_presentQueue, &presentInfo);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_window.framebufferResized)
		{
			m_window.framebufferResized = false;
			RecreateSwapChain();
		}
		else if (result != VK_SUCCESS)
		{
			Debug::Error("Echec l'or de la presentation");
		}
		m_currentFrame = (m_currentFrame + 1) % m_VulkanSynchronisation.MAX_FRAMES_IN_FLIGHT;
	}

	void RenderingEngine::RecreateSwapChain()
	{
		int width = 0, height = 0;
		glfwGetFramebufferSize(m_VulkanDeviceMisc.str_window, &width, &height);
		while (width == 0 || height == 0)
		{
			glfwGetFramebufferSize(m_VulkanDeviceMisc.str_window, &width, &height);
			glfwWaitEvents();
		}
		m_ptrf->Setting->SetWindowHeight(height);
		m_ptrf->Setting->SetWindowWidth(width);
		vkDeviceWaitIdle(m_VulkanDeviceMisc.str_device);

		RenderingEngine::m_commandBuffers.Release(&m_vulkanMisc);
		RenderingEngine::m_descriptorSets.Release(&m_vulkanMisc);
		RenderingEngine::m_descriptorPool.ReleaseImGuiPool(m_VulkanDeviceMisc.str_device);
		RenderingEngine::m_descriptorPool.Release(m_VulkanDeviceMisc.str_device);
		RenderingEngine::m_frameBuffers.Release(m_VulkanDeviceMisc.str_device);
		RenderingEngine::m_depthResources.Release(m_VulkanDeviceMisc.str_device);
		RenderingEngine::m_colorResources.Release(m_VulkanDeviceMisc.str_device);
		
		m_swapChain.rcSwapChain(&m_vulkanMisc);

		RenderingEngine::m_colorResources.Initialize(&m_vulkanMisc);
		RenderingEngine::m_depthResources.Initialize(&m_vulkanMisc);
		RenderingEngine::m_frameBuffers.Initialize(&m_vulkanMisc);
		RenderingEngine::m_descriptorPool.Initialize(&m_vulkanMisc);
		RenderingEngine::m_descriptorPool.InitializeImGuiPool(&m_vulkanMisc);
		RenderingEngine::m_descriptorSets.Initialize(&m_vulkanMisc, &m_modelLoader, &m_textureManager, &m_materialManager, &m_lightManager, &m_shaderUBdiver, m_lightManager.GetShadowManager());
		RenderingEngine::m_commandBuffers.Initialize(&m_vulkanMisc, &m_modelLoader, m_lightManager.GetShadowManager());
		m_cameraManager.updateAspectRatio();
		m_HUD.RecreateSwapChain(&m_vulkanMisc);
	}

	void RenderingEngine::RecreateDescriptorModel()
	{
		vkDeviceWaitIdle(m_VulkanDeviceMisc.str_device);
		RenderingEngine::m_commandBuffers.Release(&m_vulkanMisc);
		RenderingEngine::m_descriptorSets.Release(&m_vulkanMisc);
		RenderingEngine::m_descriptorPool.Release(m_VulkanDeviceMisc.str_device);
		if (m_textureManager.destoyTexturesState())
		{
			m_textureManager.DestroyTextures();
			m_modelLoader.MajTexture();
		}
		if (m_modelLoader.destoyModelStateBuffer())
		{
			m_modelLoader.DestroyModelBuffer();
		}		
		m_swapChain.ReCreateDescriptor(&m_vulkanMisc);
		RenderingEngine::m_descriptorPool.Initialize(&m_vulkanMisc);
		RenderingEngine::m_descriptorSets.Initialize(&m_vulkanMisc, &m_modelLoader, &m_textureManager, &m_materialManager, &m_lightManager, &m_shaderUBdiver, m_lightManager.GetShadowManager());
		RenderingEngine::m_commandBuffers.Initialize(&m_vulkanMisc, &m_modelLoader, m_lightManager.GetShadowManager());
	}
}