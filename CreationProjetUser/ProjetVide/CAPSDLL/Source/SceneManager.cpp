#include "SceneManager.hpp"


SceneManager * SceneManager::s_pInstance = nullptr;

bool SceneManager::Initialize()
{
	if (SceneManager::s_pInstance)
	{
		ge::Debug->error("SceneManager est deja initialiser");
		return false;
	
	}
	SceneManager::s_pInstance = this;
	ge::Debug->info("Initialisation des Scenes");
	m_indiceScene = -1;
#ifndef __CAPS_GAME_ENGINE__
	OnEntryRegistration();
#endif
	RegisterAllScene::RegisterALLSceneClass();
	return true;
}

void SceneManager::Release()
{
	if (m_indiceScene >= 0)
	{
		m_scene[m_indiceScene].s->UnLoad();
	}
	SceneManager::UnRegisterEntry();
	SceneManager::UnRegisterScene();
	SceneManager::s_pInstance = nullptr;
	ge::Debug->info("Liberation du SceneManager");
}

void SceneManager::LoadEntryScene()
{
	SceneManager * p_i = SceneManager::s_pInstance;
	if (p_i != nullptr)
	{
		if (p_i->m_entry)
		{
			p_i->m_entry->LoadEntryScene();
			return;
		}
		ge::Debug->warn("Entry non trouver");
		return;
	}
	ge::Debug->warn("SceneManager n'est pas initialise");
}

void SceneManager::ProjectSetting()
{
	SceneManager * p_i = SceneManager::s_pInstance;
	if (p_i)
	{
		if (p_i->m_entry)
		{
			p_i->m_entry->ProjectSetting();
			return;
		}
		ge::Debug->warn("Entry non trouver");
		return;
	}
	ge::Debug->warn("SceneManager n'est pas initialise");
}

void SceneManager::LoadLevel(std::string name)
{
	SceneManager * p_i = SceneManager::s_pInstance;
	if (p_i)
	{
		if (p_i->m_indiceScene >= 0)
		{
			p_i->m_scene[p_i->m_indiceScene].s->UnLoad();
		}
		ge::Debug->info("Chargement de la Scene %s",name.c_str());

		for (int i = 0; i < p_i->m_scene.size(); i++)
		{
			if (p_i->m_scene[i].name == name)
			{
				p_i->m_indiceScene = i;
				p_i->m_scene[i].s->Load();
				PluginManager::OnPlayAwake();
				PluginManager::OnPlayStart();
				return;
			}
		}
		ge::Debug->warn("La scene ne peut pas etre charger");
		return;
	}
	ge::Debug->warn("SceneManager n'est pas initialise");
}

void SceneManager::RegisterScene(Scene * sScene, std::string name)
{
	SceneManager * p_i = SceneManager::s_pInstance;
	ge::Debug->info("Enregistrement de la Scene %s", name.c_str());
	if (p_i)
	{
		ScenePlugin * struct_scenePlugin = new ScenePlugin();
		struct_scenePlugin->name = name;
		struct_scenePlugin->s = sScene;
		p_i->m_scene.push_back(*struct_scenePlugin);
		return;
	}
	ge::Debug->warn("SceneManager n'est pas initialise");
}

void SceneManager::RegisterEntry(Entry * sEntry)
{
	SceneManager * p_i = SceneManager::s_pInstance;
	if (p_i)
	{
		p_i->m_entry = sEntry;
		return;
	}
	ge::Debug->warn("SceneManager n'est pas initialise");
}

void SceneManager::UnRegisterScene()
{
	SceneManager * p_i = SceneManager::s_pInstance;
	if (p_i)
	{
		for (int i = 0; i < p_i->m_scene.size(); i++)
		{
			//delete(p_i->m_scene[i].s);
		}
		return;
	}
	ge::Debug->warn("SceneManager n'est pas initialise");
}

void SceneManager::UnRegisterEntry()
{
	SceneManager * p_i = SceneManager::s_pInstance;
	if (p_i)
	{
		p_i->m_entry = nullptr;
		return;
	}
	ge::Debug->warn("SceneManager n'est pas initialise");
}


