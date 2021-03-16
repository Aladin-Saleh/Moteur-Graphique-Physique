#ifndef __CAPS_SCENE_PLUGIN_MANAGER_MOTEUR__
#define __CAPS_SCENE_PLUGIN_MANAGER_MOTEUR__

#include "Debug.hpp"
#include "SettingManager.hpp"
#include "InputManager.hpp"
#include "I_ScenePMDll.hpp"
#include "CameraManager.hpp"
#ifdef _WIN32

#elif __unix__
#include <dlfcn.h>
#endif

namespace Ge
{
	class ScenePluginManagerMoteur
	{
	private:
		friend class GameEngine;
		bool Initialize(ptrF spmPtrF);
		void Release();
	public:
		void SetDllPointeurF(ptrF spmPtrF);
		I_ScenePMDll * getScenePluginManagerDLL();
	private:
		I_ScenePMDll * m_scenePluginManagerDLL;
#ifdef _WIN32
		
		HMODULE m_hDLL;
		DLL_Function_create_object_W m_pf_create;
		DLL_Function_destroy_object_W m_pf_destroy;
#elif __unix__
		void* m_hDLL;
		I_ScenePMDll* (*create)();
		void(*destroy)(I_ScenePMDll*);
#endif

	};
}

#endif //__CAPS_SCENE_PLUGIN_MANAGER_MOTEUR__
