#ifndef __CAPS_SCENE_1__
#define __CAPS_SCENE_1__

#include "SceneManager.hpp"
#include "PluginManager.hpp"
#include "Scene.hpp"
#include "Plugin.hpp"
#include "Skybox.hpp"

class Scene1 : public Scene
{
public:
	void Load() final;
	void UnLoad() final;
private:
};

#endif