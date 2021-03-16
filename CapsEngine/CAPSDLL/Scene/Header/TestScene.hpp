#ifndef __CAPS_TEST_SCENE__
#define __CAPS_TEST_SCENE__

#include "SceneManager.hpp"
#include "PluginManager.hpp"
#include "TestPlugin.hpp"
#include "PluginTest2.hpp"
#include "Scene.hpp"
#include "Plugin.hpp"

class TestScene : public Scene
{
public:
	void Load() final;
	void UnLoad() final;
private:
//	TestPlugin * p_TestPlugin;
};

#endif