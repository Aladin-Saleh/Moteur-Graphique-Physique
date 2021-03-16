#include "Scene1.hpp"

void Scene1::Load()
{
	PluginManager::RegisterPlugin(new Skybox());
}

void Scene1::UnLoad()
{
	PluginManager::UnregisterAllPlugin();
}
