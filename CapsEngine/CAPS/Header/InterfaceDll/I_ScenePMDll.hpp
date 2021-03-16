#ifndef __CAPS_INTERFACE_SCENE_PLUGIN_DLL__
#define __CAPS_INTERFACE_SCENE_PLUGIN_DLL__

#include "PointeurFonction.hpp"

class I_ScenePMDll
{
public:
	virtual void Initialize() = 0;
	virtual void Release() = 0;
	virtual void SetFonction(ptrF f) = 0;
	virtual void LoadEntryScene() = 0;
	virtual void ProjectSetting() = 0;
	virtual void OnPreUpdate() = 0;
	virtual void OnPostUpdate() = 0;
	virtual void OnGUI() = 0;
};

#ifdef _WIN32 
#if defined (__cplusplus)
extern "C" {
#endif
#include <windows.h>
	typedef I_ScenePMDll * (WINAPI * DLL_Function_create_object_W) ();
	typedef void (WINAPI * DLL_Function_destroy_object_W) (I_ScenePMDll * object);
#if defined (__cplusplus)
}
#endif
#endif

#endif //!__CAPS_INTERFACE_SCENE_PLUGIN_DLL__