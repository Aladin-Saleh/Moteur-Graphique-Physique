#ifndef __CAPS_POINTEUR_FONCTION__
#define __CAPS_POINTEUR_FONCTION__

#include "I_InputManager.hpp"
#include "I_Debug.hpp"
#include "I_SettingManager.hpp"
#include "I_CameraManager.hpp"
#include "I_SoundEngine.hpp"
#include "I_Time.hpp"
#include "I_ModelManager.hpp"
#include "Model.hpp"
#include "ShapeBuffer.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "I_TextureManager.hpp"
#include "I_PhysicsEngine.hpp"
#include "I_MaterialManager.hpp"
#include "I_LightManager.hpp"
#include "I_RayCast.hpp"
#include "GUI.hpp"

struct ptrF
{
	I_InputManager * InputManager = nullptr;
	I_Debug * Debug = nullptr;
	I_SettingManager * Setting = nullptr;
	I_CameraManager * Camera = nullptr;
	I_SoundEngine * Sound = nullptr;
	I_Time * Time = nullptr;
	I_ModelManager * ModelManager = nullptr;
	I_TextureManager * TextureManager = nullptr;
	I_PhysicsEngine * PhysicsEngine = nullptr;
	I_MaterialManager * MaterialManager = nullptr;
	I_LightManager * LightManager = nullptr;
	I_RayCast * RayCast = nullptr;
	Gui * ui = nullptr;
};

#endif //!__CAPS_POINTEUR_FONCTION__