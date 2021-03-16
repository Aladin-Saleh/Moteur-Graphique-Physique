#ifndef __CAPS_WINDOW__
#define __CAPS_WINDOW__

#include "Debug.hpp"
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include "VulkanMisc.hpp"

namespace Ge
{
	class Window
	{
	public:
		static void framebufferResizeCallback(GLFWwindow* window,int width,int height);
	private:
		friend class RenderingEngine;
		bool InitWindow(uint32_t Width, uint32_t Height, const char * name, VulkanDeviceMisc * vdc);
		void Release();
	private:
		friend class RenderingEngine;
		bool framebufferResized = false;
		GLFWwindow * m_window;
	};
}
#endif