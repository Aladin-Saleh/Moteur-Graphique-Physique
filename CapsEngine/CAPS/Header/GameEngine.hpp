#ifndef __CAPS_GAME_ENGINE__
#define __CAPS_GAME_ENGINE__

#include "Debug.hpp"
#include "SettingManager.hpp"
#include "RenderingEngine.hpp"
#include "ScenePluginManagerMoteur.hpp"
#include "Window.hpp"
#include "InputManager.hpp"
#include "Time.hpp"
#include "SoundEngine.hpp"
#include "VulkanMisc.hpp"
#include "PhysicsEngine.hpp"

namespace Ge
{
	class GameEngine
	{
	public:
		bool Initialize();
		void Release();
		void Start();
	private:
		void Update();
	private:
		SettingManager m_settingManager;
		RenderingEngine m_renderingEngine;
		ScenePluginManagerMoteur m_scenePluginManagerMoteur;
		InputManager m_inputManager;
		Debug m_debug;
		Time m_time;
		SoundEngine m_soundManager;
		PhysicsEngine m_physicsEngine;
		ptrF m_SPMM_PtrF;
		I_ScenePMDll * m_scenePluginManagerDLL;
		VulkanMisc * m_VulkanMisc;
		float m_lag = 0.0f;
	};
}

#endif //__CAPS_GAME_ENGINE__