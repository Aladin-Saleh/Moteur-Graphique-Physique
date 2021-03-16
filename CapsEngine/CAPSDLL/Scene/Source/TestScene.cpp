#include "TestScene.hpp"

void TestScene::Load()
{
	PluginManager::RegisterPlugin(new TestPlugin());
	//PluginManager::RegisterPlugin(new PluginTest2());
}

void TestScene::UnLoad()
{
	PluginManager::UnregisterAllPlugin();
}
