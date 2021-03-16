#include "Window.hpp"

namespace Ge
{

	bool Window::InitWindow(uint32_t Width, uint32_t Height, const char * name, VulkanDeviceMisc * vdc)
	{
		glfwInit();//init la fenetre

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);/*ne cree pas de context OpenGl*/

		this->m_window = glfwCreateWindow(Width, Height, name, nullptr, nullptr);/*3: Moniteur 4: Specifique a OpenGl*/
		glfwSetWindowUserPointer(this->m_window, this);//on fournie la class a la fenetre
		glfwSetFramebufferSizeCallback(this->m_window, this->framebufferResizeCallback);//utiliser une fonction statique car GLFW ne sait pas correctement appeler une fonction membre
		vdc->str_window = this->m_window;
		Debug::Info("Initialisation de la fenetre");
		return true;
	}

	void Window::Release()
	{
		glfwDestroyWindow(this->m_window);/*DestroyWindow*/
		glfwTerminate();
		Debug::Info("Liberation de la fenetre");
	}

	void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		/*callback de redimentionement pour glfw avec la mise a jour du parametre framebufferResized
		 pour pouvoir indiquer a la swap chain quil faut ce redimentionner*/
		auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		win->framebufferResized = true;
		Debug::Info("Redimension de la fenetre : %d , %d", nullptr,width,height);
	}
}