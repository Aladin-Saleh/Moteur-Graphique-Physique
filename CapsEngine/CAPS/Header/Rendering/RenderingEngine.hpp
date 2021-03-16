#ifndef __CAPS_RENDERING_ENGINE__
#define __CAPS_RENDERING_ENGINE__

#include "Debug.hpp"
#include "Window.hpp"
#include "ValidationLayer.hpp"
#include "InstanceV.hpp"
#include "SettingManager.hpp"
#include "WindowSurface.hpp"
#include "PhysicalDevices.hpp"
#include "LogicalDevice.hpp"
#include "SwapChain.hpp"
#include "CommandPool.hpp"
#include "ColorResources.hpp"
#include "DepthResources.hpp"
#include "Framebuffers.hpp"
#include "TextureManager.hpp"
#include "Model_Manager.hpp"
#include "BufferManager.hpp"
#include "DescriptorPool.hpp"
#include "DescriptorSets.hpp"
#include "CommandBuffers.hpp"
#include "SyncObjects.hpp"
#include "Caps_HUD.hpp"
#include "CameraManager.hpp"
#include "ShaderUBdiver.hpp"
#include "MaterialManager.hpp"
#include "LightManager.hpp"
#include "PointeurFonction.hpp"
#include "VulkanMisc.hpp"

namespace Ge
{
	class RenderingEngine
	{
	private:
		friend class GameEngine;
		VulkanMisc * Initialize(ptrF * ptrf, SoundEngine * se, PhysicsEngine * pe);
		void Release();
		ConsoleDebug * getConsoleDebug();
		void DrawFrame();
	private:
		void RecreateSwapChain();
		void RecreateDescriptorModel();
	private:
		VulkanMisc m_vulkanMisc;
		VulkanDeviceMisc m_VulkanDeviceMisc;
		VulkanSwapChainMisc m_VulkanSwapChainMisc;
		VulkanCommandeBufferMisc m_VulkanCommandeBufferMisc;
		VulkanDescriptor m_VulkanDescriptor;
		VulkanSynchronisation m_VulkanSynchronisation;

		ptrF * m_ptrf;
		Window m_window;
		ValidationLayer m_validationLayer;
		InstanceV m_instanceV;
		WindowSurface m_windowSurface;
		PhysicalDevices m_physicalDevice;
		LogicalDevice m_logicalDevice;
		SwapChain m_swapChain;
		CommandPool m_commandPool;
		ColorResources m_colorResources;
		DepthResources m_depthResources;
		FrameBuffers m_frameBuffers;
		TextureManager m_textureManager;
		Model_Manager m_modelLoader;
		DescriptorPool m_descriptorPool;
		DescriptorSets m_descriptorSets;
		CommandBuffers m_commandBuffers;
		BufferManager m_bufferManager;
		SyncObjects m_syncObjects;
		Caps_HUD m_HUD;
		CameraManager m_cameraManager;
		ShaderUBdiver m_shaderUBdiver;
		MaterialManager m_materialManager;
		LightManager m_lightManager;
		size_t m_currentFrame = 0;
	}; 
}
#endif