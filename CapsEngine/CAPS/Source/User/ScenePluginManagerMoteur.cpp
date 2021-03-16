#include "ScenePluginManagerMoteur.hpp"

namespace Ge
{
	bool ScenePluginManagerMoteur::Initialize(ptrF spmPtrF)
	{
#ifdef _WIN32 

		m_hDLL = LoadLibrary("../buildDLL/CAPSDLL_Debug.dll");
		if (m_hDLL != NULL)
		{
			Debug::Info("Ouverture de la DLL");
			m_pf_create = (DLL_Function_create_object_W)GetProcAddress(m_hDLL, "create_object_W");
			if (m_pf_create != NULL)
			{
				m_pf_destroy = (DLL_Function_destroy_object_W)GetProcAddress(m_hDLL, "destroy_object_W");
				if (m_pf_destroy != NULL)
				{
					Debug::Info("Succes dans la recuperation des fonction d'instance.");
					m_scenePluginManagerDLL = m_pf_create();
					ScenePluginManagerMoteur::SetDllPointeurF(spmPtrF);
					m_scenePluginManagerDLL->Initialize();
				}
				else
				{
					Debug::Error("Erreur dans la recuperation de la fonction ! ");
				}
			}
			else
			{
				Debug::Error("Erreur dans la recuperation de la fonction ! ");
			}
			
			
		}
		else
		{
			Debug::Error("Erreur dans l'ouvertre de la DLL ! ");
		}
		
		

		
		
		
#elif __unix__
		m_hDLL = dlopen("../CAPSDLL/libCAPSDLL.so", RTLD_LAZY);
		if (m_hDLL != nullptr)
		{
			Debug::Info("Ouverture de la DLL");
			create = (I_ScenePMDll* (*)())dlsym(m_hDLL, "create_object");
			if (create != nullptr)
			{
				destroy = (void(*)(I_ScenePMDll*))dlsym(m_hDLL, "destroy_object");

				if (destroy != nullptr)
				{
					Debug::Info("Succes dans la recuperation des fonction d'instance.");
					m_scenePluginManagerDLL = (I_ScenePMDll*)create();
					ScenePluginManagerMoteur::SetDllPointeurF(spmPtrF);
					m_scenePluginManagerDLL->Initialize();
				}
				else
				{
					Debug::Error("Erreur dans la recuperation de la fonction ! ");
					return false;
				}

			}
			else
			{
				Debug::Error("Erreur dans la recuperation de la fonction ! ");
				return false;

			}
		}
		else
		{
			Debug::Error("Erreur dans l'ouvertre de la librarie dynamique ! ");
			return false;
		}
#else
		Debug::Error("Plateforme non detectee");
		return false;
#endif
		Debug::Info("Initialisation des Scenes et Plugin");

		return true;
	}

	void ScenePluginManagerMoteur::Release()
	{
		m_scenePluginManagerDLL->Release();
#ifdef _WIN32
		
		m_pf_destroy(m_scenePluginManagerDLL);
		FreeLibrary(m_hDLL);
		


#elif __unix__

		destroy(m_scenePluginManagerDLL);
		dlclose(m_hDLL);
#endif

		Debug::Info("Liberation de la DLL");
		Debug::Info("Liberation des Scenes et Plugin");
	}

	void ScenePluginManagerMoteur::SetDllPointeurF(ptrF  spmPtrF)
	{
		m_scenePluginManagerDLL->SetFonction(spmPtrF);
	}

	I_ScenePMDll * ScenePluginManagerMoteur::getScenePluginManagerDLL()
	{
		return m_scenePluginManagerDLL;
	}
}