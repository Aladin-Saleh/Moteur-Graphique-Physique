#ifndef __CAPS_AAA_SCENE__
#define __CAPS_AAA_SCENE__

#include "SceneManager.hpp"
#include "PluginManager.hpp"
#include "Scene.hpp"
#include "PluginTest2.hpp"


class AAA : public Scene
{
public:
	void Load() final;
	void UnLoad() final;
public:
	Audio * audio01;
	ShapeBuffer * buffer;
	Model * shape;
	ShapeBuffer * buffer2;
	Model * shape2;
	ShapeBuffer * buffer3;
	Model * shape3;
	Texture * craneTexture;
	Texture * testTexture;
	Texture * poupeTexture;
	std::vector<Model *> testModel;
};

#endif