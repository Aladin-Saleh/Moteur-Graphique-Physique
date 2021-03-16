#ifndef __CAPS_REGISTER_ALL_SCENE__
#define __CAPS_REGISTER_ALL_SCENE__
//Include Scene du projet(Dans le projet Final ce script sera automatiquement remplie)
#ifndef __CAPS_GAME_ENGINE__
#include "TestScene.hpp"
#include "AAA.hpp"
#endif
//####

#include "Scene.hpp"
#include "SceneManager.hpp"
#include <vector>

class RegisterAllScene
{
private:
	friend class SceneManager;
	static void RegisterALLSceneClass();
};

#endif //!__CAPS_REGISTER_ALL_SCENE__