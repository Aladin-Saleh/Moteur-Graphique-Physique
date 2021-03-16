#include "PluginManager.hpp"


PluginManager * PluginManager::s_pInstance = nullptr;

bool PluginManager::Initialize()
{
	if (PluginManager::s_pInstance)
	{
		ge::Debug->error("SceneManager est deja initialiser");
		return false;
	}
	PluginManager::s_pInstance = this;
	ge::Debug->info("Initialisation des Plugin");
	return true;
}

void PluginManager::Release()
{
	PluginManager::s_pInstance = nullptr;
}

void PluginManager::RegisterPlugin(Plugin * pPlugin)
{
	PluginManager * p_i = PluginManager::s_pInstance;
	if (p_i)
	{
		if (pPlugin != nullptr)
		{
			//pPlugin->OnPlayAwake();
			//pPlugin->OnPlayStart();
			p_i->m_plugin.push_back(pPlugin);
			return;
		}
		ge::Debug->warn("Register plugin nullptr");
		return;
	}
	ge::Debug->warn("PluginManager n'est pas initialise");
}

void PluginManager::UnregisterPlugin(Plugin * pPlugin)
{
	PluginManager * p_i = PluginManager::s_pInstance;
	if (p_i)
	{
		if (pPlugin != nullptr)
		{
			pPlugin->OnPlayStop();
			for (int i = 0; i < p_i->m_plugin.size(); i++)
			{
				if (p_i->m_plugin[i] == pPlugin)
				{
					p_i->m_plugin.erase(p_i->m_plugin.begin() + i);
					delete(pPlugin);
					return;
				}
			}
		}
		ge::Debug->warn("UnregisterPlugin plugin nullptr");
		return;
	}
	ge::Debug->warn("PluginManager n'est pas initialise");
}

void PluginManager::UnregisterAllPlugin()
{
	PluginManager * p_i = PluginManager::s_pInstance;
	if (p_i)
	{
		PluginManager::OnPlayStop();
		p_i->m_plugin.clear();
		return;
	}
	ge::Debug->warn("PluginManager n'est pas initialise");
}

void PluginManager::OnPlayAwake()
{
	if (PluginManager::s_pInstance)
	{
		for (int i = 0; i < PluginManager::s_pInstance->m_plugin.size(); i++)
		{
			PluginManager::s_pInstance->m_plugin[i]->OnPlayAwake();
		}
		return;
	}
	ge::Debug->warn("PluginManager n'est pas initialise");
}

void PluginManager::OnPlayStart()
{
	if (PluginManager::s_pInstance)
	{
		for (int i = 0; i < PluginManager::s_pInstance->m_plugin.size(); i++)
		{
			PluginManager::s_pInstance->m_plugin[i]->OnPlayStart();
		}
		return;
	}
	ge::Debug->warn("PluginManager n'est pas initialise");
}

void PluginManager::OnPreUpdate()
{
	if (PluginManager::s_pInstance)
	{
		for (int i = 0; i < PluginManager::s_pInstance->m_plugin.size(); i++)
		{
			PluginManager::s_pInstance->m_plugin[i]->OnPreUpdate();
		}
		return;
	}
	ge::Debug->warn("PluginManager n'est pas initialise");
}

void PluginManager::OnPostUpdate()
{
	if (PluginManager::s_pInstance)
	{
		for (int i = 0; i < PluginManager::s_pInstance->m_plugin.size(); i++)
		{
			PluginManager::s_pInstance->m_plugin[i]->OnPostUpdate();
		}
		return;
	}
	ge::Debug->warn("PluginManager n'est pas initialise");
}

void PluginManager::OnGUI()
{
	if (PluginManager::s_pInstance)
	{
		for (int i = 0; i < PluginManager::s_pInstance->m_plugin.size(); i++)
		{
			PluginManager::s_pInstance->m_plugin[i]->OnGUI();
		}
		return;
	}
	ge::Debug->warn("PluginManager n'est pas initialise");
}

void PluginManager::OnTriggerEnter(Plugin * pPlugin)
{
}

void PluginManager::OnTriggerExit(Plugin * pPlugin)
{
}

void PluginManager::OnTriggerStay(Plugin * pPlugin)
{
}

void PluginManager::OnPlayStop()
{
	if (PluginManager::s_pInstance)
	{
		for (int i = 0; i < PluginManager::s_pInstance->m_plugin.size(); i++)
		{
			PluginManager::s_pInstance->m_plugin[i]->OnPlayStop();
		}
		return;
	}
	ge::Debug->warn("PluginManager n'est pas initialise");
}
