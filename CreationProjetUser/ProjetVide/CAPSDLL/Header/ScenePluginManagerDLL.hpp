#ifndef __CAPS_SCENE_PLUGIN_MANAGER_DLL__
#define __CAPS_SCENE_PLUGIN_MANAGER_DLL__

#include "SceneManager.hpp"
#include "PluginManager.hpp"
#include "Entry.hpp"
#include "Plugin.hpp"
#include "Scene.hpp"
#include "EngineFonction.hpp"
#include "I_ScenePMDll.hpp"

class ScenePluginManagerDLL : public I_ScenePMDll
{
public:
	void Initialize();
	void Release();
	void SetFonction(ptrF f);
	void LoadEntryScene();
	void ProjectSetting();
	void OnPreUpdate();
	void OnPostUpdate();
	void OnGUI();
private:
	EngineFonction m_engineFonction;
	SceneManager m_sceneManager;
	PluginManager m_pluginManager;
};

#endif
