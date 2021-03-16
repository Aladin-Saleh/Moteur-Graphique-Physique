#include "RegisterALLScene.hpp"

void RegisterAllScene::RegisterALLSceneClass()
{
#ifndef __CAPS_GAME_ENGINE__
	SceneManager::RegisterScene(new TestScene(),"Scene1");
	SceneManager::RegisterScene(new AAA(), "SceneAAA");
#endif
}
