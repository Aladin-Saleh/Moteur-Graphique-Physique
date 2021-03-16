#ifndef __CAPS_SCENE_ALADIN_SCENE__
#define __CAPS_SCENE_ALADIN_SCENE__

#include "SceneManager.hpp"
#include "PluginManager.hpp"
#include "Scene.hpp"
#include "PluginTest2.hpp"


class Scene_Aladin : public Scene
{
public:
	void Load() final;
	void UnLoad() final;
public:
	Audio* audio01;
	ShapeBuffer* bufferPlate;
	Model* shape;
	ShapeBuffer* buffer2;
	Model* shape2;
	ShapeBuffer* buffer3;
	Model* shape3;
	Texture* craneTexture;
	Texture* testTexture;
	Texture* poupeTexture;
	std::vector<Model*> testModel;
};

#endif