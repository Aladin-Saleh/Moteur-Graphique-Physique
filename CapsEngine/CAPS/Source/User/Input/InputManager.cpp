#include "InputManager.hpp"

namespace Ge
{
	bool InputManager::Initialize(VulkanDeviceMisc vulkanDevice)
	{
		Debug::Info("Initialisation de l'InputManager");
		m_window = vulkanDevice.str_window;
		return true;
	}

	void InputManager::UpdateAxis()
	{
		glfwGetCursorPos(m_window, &m_Mpos.x, &m_Mpos.y);
		m_axisMouse = m_Mpos - m_lastMousePos;	
		m_lastMousePos = m_Mpos;
	}

	void InputManager::Release()
	{
		Debug::Info("Liberation de l'InputManager");
	}

	const char * InputManager::GetGamepadName(int jid)
	{
		return glfwGetGamepadName(jid);
	}

	bool InputManager::GetGamepadState(int jid, int key)
	{
		GLFWgamepadstate state;
		glfwGetGamepadState(jid, &state);
		if (key > 15)
		{
			return false;
		}
		return state.buttons[key] == GLFW_PRESS;
	}

	float InputManager::GetGamepadAxis(int jid, int indice)
	{
		GLFWgamepadstate state;
		glfwGetGamepadState(jid, &state);
		if (indice > 5)
		{
			Debug::Error("l'indice de GetGamepadAxis n'existe pas");
			return -2;
		}
		return state.axes[indice];
	}

	bool InputManager::GetKey(int key)
	{
		return glfwGetKey(m_window, key) == GLFW_PRESS;
	}

	bool InputManager::GetKeyUp(int key)
	{
		if (mapReleasedInput.find(key) == mapReleasedInput.end())
		{
			mapReleasedInput[key] = false;
		}
		if (glfwGetKey(m_window, key) == GLFW_PRESS)
		{
			mapReleasedInput[key] = true;
			return false;
		}
		else
		{
			if (mapReleasedInput[key])
			{
				mapReleasedInput[key] = false;
				return true;
			}

		}
		return false;
	}

	bool InputManager::GetKeyDown(int key)
	{
		if (mapPressedInput.find(key) == mapPressedInput.end())
		{
			mapPressedInput[key] = false;
		}
		if (glfwGetKey(m_window, key) == GLFW_PRESS)
		{
			if (!mapPressedInput[key])
			{
				mapPressedInput[key] = true;
				return true;
			}
		}
		else
		{
			mapPressedInput[key] = false;
		}
		return false;
	}

	bool InputManager::GetMouse(int key)
	{
		return glfwGetMouseButton(m_window, key) == GLFW_PRESS;
	}

	double InputManager::AxisMouseX()
	{
		return m_axisMouse.x;
	}

	double InputManager::AxisMouseY()
	{
		return m_axisMouse.y;
	}

	double InputManager::GetMousePosX()
	{
		return m_Mpos.x;
	}

	double InputManager::GetMousePosY()
	{
		return m_Mpos.y;
	}

}