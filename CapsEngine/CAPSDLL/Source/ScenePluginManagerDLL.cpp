#include "ScenePluginManagerDLL.hpp"

#ifdef _WIN32 
#include <Windows.h>
BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return true;
}

extern "C" I_ScenePMDll * WINAPI create_object_W()
{
	return new ScenePluginManagerDLL;
}

extern "C" void WINAPI destroy_object_W(I_ScenePMDll * object)
{
	delete object;
}

#elif __unix__

extern "C" ScenePluginManagerDLL* create_object()
{
	return new ScenePluginManagerDLL;
}

extern "C" void destroy_object(ScenePluginManagerDLL* object)
{
	delete object;
}

#endif

void ScenePluginManagerDLL::Initialize()
{
	m_pluginManager.Initialize();
	m_sceneManager.Initialize();
}

void ScenePluginManagerDLL::Release()
{
	m_sceneManager.Release();
	m_pluginManager.Release();
	m_engineFonction.Release();
}

void ScenePluginManagerDLL::SetFonction(ptrF f)
{
	m_engineFonction.Initialize(f);
}


void ScenePluginManagerDLL::LoadEntryScene()
{
	m_sceneManager.LoadEntryScene();
}

void ScenePluginManagerDLL::ProjectSetting()
{
	SceneManager::ProjectSetting();
}


void ScenePluginManagerDLL::OnPreUpdate()
{
	m_pluginManager.OnPreUpdate();
}

void ScenePluginManagerDLL::OnPostUpdate()
{
	m_pluginManager.OnPostUpdate();
}

void ScenePluginManagerDLL::OnGUI()
{
	m_pluginManager.OnGUI();
}

