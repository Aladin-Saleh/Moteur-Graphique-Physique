#ifndef __CAPS_SCENE_MANAGER__
#define __CAPS_SCENE_MANAGER__

#include "Scene.hpp"
#include "Entry.hpp"
#include <vector>
#include <iostream>
#include <string>
#include "RegisterALLScene.hpp"

class SceneManager
{
	struct ScenePlugin
	{
		Scene * s;
		std::string name;
	};
private:
	friend class ScenePluginManagerDLL;
	bool Initialize();
	void Release();
public:
	static void LoadEntryScene();
	static void ProjectSetting();
	static void LoadLevel(std::string name);
	static void RegisterScene(Scene * sScene, std::string name);
	static void RegisterEntry(Entry * sEntry);
	static void UnRegisterScene();
	static void UnRegisterEntry();
private:
	static SceneManager * s_pInstance;
	std::vector<ScenePlugin> m_scene;
	Entry * m_entry;
	int m_indiceScene;
};


#endif