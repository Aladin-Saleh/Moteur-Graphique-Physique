#ifndef __CAPS_ENGINE_FONCTION__
#define __CAPS_ENGINE_FONCTION__

#include "SettingManagerStruct.hpp"
#include "InputDefine.hpp"
#include "PhysicsDefine.hpp"
#include "PointeurFonction.hpp"

class EngineFonction
{
private:
	friend class ScenePluginManagerDLL;
	bool Initialize(ptrF f);
	void Release();
public:
	static I_InputManager * Input;
	static I_Debug * Debug;
	static I_SettingManager* Setting;
	static I_CameraManager* Camera;
	static I_SoundEngine* Sound;
	static I_Time* Time;
	static I_ModelManager* ModelManager;
	static I_TextureManager* TextureManager;
	static I_PhysicsEngine * PhysicsEngine;
	static I_MaterialManager * MaterialManager;
	static I_LightManager * LightManager;
	static I_RayCast * RayCast;
	static Gui * ui;
private:
	static EngineFonction * s_pInstance;
	ptrF pFonction;
};

#define ge EngineFonction
#endif //__CAPS_ENGINE_FONCTION__