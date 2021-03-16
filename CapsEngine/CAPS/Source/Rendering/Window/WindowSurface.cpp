#include "WindowSurface.hpp"

namespace Ge
{

	bool WindowSurface::Initialize(VulkanDeviceMisc * vDM)
	{
		if(glfwCreateWindowSurface(vDM->str_instance, vDM->str_window, nullptr, &m_surface) != VK_SUCCESS)// creation de la la VkSurfaceKHR pour faire le rendu sur la fenetre via la swap chain
		{
			Debug::Error("echec de la creation de la window surface");
			return false;
		}
		vDM->str_surface = m_surface;
		Debug::Info("Initialisation de la WindowSurface");
		return true;
	}

	void WindowSurface::Release(VulkanDeviceMisc * vDM)
	{		
		vkDestroySurfaceKHR(vDM->str_instance, m_surface, nullptr);// destruction la window surface
		vDM->str_surface = VK_NULL_HANDLE;
		Debug::Info("Liberation de la WindowSurface");
	}

	void WindowSurface::SetupPresentQueue(VkDevice device, unsigned int value, VulkanDeviceMisc * vDM)
	{
		vkGetDeviceQueue(device, value, 0, &m_presentQueue);
	}
}