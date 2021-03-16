#ifndef __CAPS_PLUGIN_MANAGER__
#define __CAPS_PLUGIN_MANAGER__

#include "Plugin.hpp"
#include <vector>


class PluginManager
{
private:
	friend class ScenePluginManagerDLL;
	bool Initialize();
	void Release();
public:
	static void RegisterPlugin(Plugin * pPlugin);
	static void UnregisterPlugin(Plugin * pPlugin);
	static void UnregisterAllPlugin();
	static void OnPlayAwake();
	static void OnPlayStart();
	static void OnPreUpdate();
	static void OnPostUpdate();
	static void OnGUI();
	static void OnTriggerEnter(Plugin * pPlugin);
	static void OnTriggerExit(Plugin * pPlugin);
	static void OnTriggerStay(Plugin * pPlugin);
	static void OnPlayStop();
private:
	static PluginManager * s_pInstance;
	std::vector<Plugin*> m_plugin;
};


#endif //__CAPS_PLUGIN_MANAGER__