#ifndef __CAPS_INPUT_MANAGER__
#define __CAPS_INPUT_MANAGER__

#include "Window.hpp"
#include "GLFW/glfw3.h"
#include <map>
#include "Debug.hpp"
#include "I_InputManager.hpp"
#include "glm/glm.hpp"
#include "PointeurFonction.hpp"
#include "RenderingEngine.hpp"

namespace Ge
{
	class InputManager : public I_InputManager
	{
	private:
		friend class GameEngine;
		bool Initialize(VulkanDeviceMisc vulkanDevice);
		void UpdateAxis();
		void Release();
	public:
		const char * GetGamepadName(int jid);
		bool GetGamepadState(int jid,int key);
		float GetGamepadAxis(int jid, int indice);
		bool GetKey(int key);
		bool GetKeyUp(int key);
		bool GetKeyDown(int key);
		bool GetMouse(int key);
		double AxisMouseX();
		double AxisMouseY();
		double GetMousePosX();
		double GetMousePosY();
	private:
		std::map<int, bool> mapPressedInput;
		std::map<int, bool> mapReleasedInput;
		glm::tvec2<double> m_lastMousePos;
		glm::tvec2<double> m_axisMouse;
		glm::tvec2<double> m_Mpos;
		GLFWwindow * m_window;
	};
}

#endif // !__CAPS_INPUT_MANAGER__