#ifndef __CAPS_HUD__
#define __CAPS_HUD__

#include "Debug.hpp"
#define GLFW_INCLUDE_NONE
#include "imgui-cmake/Header/imgui.h"
#include "imgui-cmake/Header/imgui_impl_vulkan.h"
#include "imgui-cmake/Header/imgui_impl_glfw.h"
#include "VulkanMisc.hpp"
#include "Rendering/ImGui/Caps_Console_HUD.hpp"
#include <vector>
#include "GObject.hpp"
#include "MShape.hpp"
#include "PointeurFonction.hpp"
#include "Model_Manager.hpp"
#include "HiearchyGUI.hpp"
#include "ProjectGUI.hpp"
#include "GUI.hpp"

namespace Ge
{

  
	class Caps_HUD : public Gui
	{


	public:
		friend class RenderingEngine;
		bool Init_HUD(VulkanMisc* vM, Model_Manager * mm, LightManager * lm, PhysicsEngine * pe, SoundEngine * se, CameraManager * cm);
		void ReleaseHUD(VkDevice device);
		void RecreateSwapChain(VulkanMisc* vM);
		void Render(VulkanMisc * vM, uint32_t currentframe);
		static void check_vk_result(VkResult err);
		void MenuBar(bool* p_open, bool* is_UI_is_active);
		void InfoSystem(VulkanMisc* vM);
		void Ips();
		void OverlayInfo(VulkanMisc* vM, bool* p_open);
		void Console_Debug(VulkanMisc* vM);
		void UpdateHierachy();
		void HierachyAffichage();
		void SetModelManager(Model_Manager* mM);
		void setActiveUI(bool state);
		ConsoleDebug * getConsoleDebug();
	private:
		bool createCommandPool(VkCommandPool* commandPool, VkCommandPoolCreateFlags flags, VulkanDeviceMisc * vM);
		bool createCommandBuffers(VkCommandBuffer* commandBuffer, uint32_t commandBufferCount, VkCommandPool &commandPool, VulkanDeviceMisc * vM);
		void ImGuiRender(VulkanMisc* vM);
	private:
		friend class RenderingEngine;
		VkRenderPass m_imGuiRenderPass;
		ImGui_ImplVulkanH_Window * m_vWindow;
		VkCommandPool m_imGuiCommandPools;
		std::vector<VkFramebuffer> m_imGuiFramebuffer;
		std::vector<VkCommandBuffer> m_imGuiCommandBuffers;
		std::array<VkClearValue, 2> m_clearValues{};
		std::vector<GObject*> m_gObjects;
		std::vector<MShape*> m_model;	
		Model_Manager* m_modelLoader;
		HiearchyGUI * m_hiearchyGUI;
		ProjectGUI * m_projectGUI;
		Model_Manager * m_ModelManager;
		LightManager * m_LightManager;
		PhysicsEngine * m_PhysicsEngine;
		SoundEngine * m_SoundEngine;
		CameraManager * m_CameraManager;
		ConsoleDebug m_console_HUD;
		bool isHUDActive;
		bool m_GlobalGUIActive = true;
	};

}



#endif