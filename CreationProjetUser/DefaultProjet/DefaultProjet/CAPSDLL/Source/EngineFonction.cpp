#include "EngineFonction.hpp"

EngineFonction * EngineFonction::s_pInstance = nullptr;
I_InputManager * EngineFonction::Input = nullptr;
I_Debug * EngineFonction::Debug = nullptr;
I_SettingManager* EngineFonction::Setting = nullptr;
I_CameraManager* EngineFonction::Camera = nullptr;
I_SoundEngine* EngineFonction::Sound = nullptr;
I_Time* EngineFonction::Time = nullptr;
I_ModelManager* EngineFonction::ModelManager = nullptr;
I_TextureManager* EngineFonction::TextureManager = nullptr;
I_PhysicsEngine* EngineFonction::PhysicsEngine = nullptr;
I_MaterialManager * EngineFonction::MaterialManager = nullptr;
I_LightManager * EngineFonction::LightManager = nullptr;
I_RayCast * EngineFonction::RayCast = nullptr;
Gui * EngineFonction::ui = nullptr;

bool EngineFonction::Initialize(ptrF f)
{
	pFonction = f;
	Input = f.InputManager;
	Debug = f.Debug;
	Setting = f.Setting;
	Camera = f.Camera;
	Sound = f.Sound;
	Time = f.Time;
	ModelManager = f.ModelManager;
	TextureManager = f.TextureManager;
	PhysicsEngine = f.PhysicsEngine;
	MaterialManager = f.MaterialManager;
	LightManager = f.LightManager;
	RayCast = f.RayCast;
	ui = f.ui;
	EngineFonction::s_pInstance = this;
	return true;
}

void EngineFonction::Release()
{
	EngineFonction::s_pInstance = nullptr;
}


