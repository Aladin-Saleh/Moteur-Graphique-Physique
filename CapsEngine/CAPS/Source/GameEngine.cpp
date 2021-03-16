#include "GameEngine.hpp"

namespace Ge
{
	bool GameEngine::Initialize()
	{ 
		Debug::Info("Initialisation Moteur");
		if (!m_debug.Initialize(&m_SPMM_PtrF))
		{
			Debug::Error("Erreur d'initialisation du debug");
			return false;
		}
		if (!m_settingManager.Initialize(&m_SPMM_PtrF))
		{
			Debug::Error("Erreur d'initialisation des parametres");
			return false;
		}
		m_SPMM_PtrF.Time = &m_time;
		if (!m_scenePluginManagerMoteur.Initialize(m_SPMM_PtrF))
		{
			Debug::Error("Erreur d'initialisation du manager de Scene et plugin");
			return false;
		}
		m_scenePluginManagerDLL = m_scenePluginManagerMoteur.getScenePluginManagerDLL();
		m_scenePluginManagerDLL->ProjectSetting();
		m_SPMM_PtrF.InputManager = (I_InputManager *)&m_inputManager;
		m_VulkanMisc = m_renderingEngine.Initialize(&m_SPMM_PtrF,&m_soundManager, &m_physicsEngine);
		m_debug.setConsoleDebug(m_renderingEngine.getConsoleDebug());
		if (!m_inputManager.Initialize(*m_VulkanMisc->str_VulkanDeviceMisc))
		{
			Debug::Error("Erreur d'initialisation des touches");
			return false;
		}
		if (!m_soundManager.Initialize())
		{
			Debug::Error("Erreur d'initialisation du sound manager");
			return false;
		}
		if (!m_physicsEngine.Initialize(m_settingManager.GetGravity()))
		{
			Debug::Error("Erreur d'initialisation du moteur physique");
			return false;
		}
		m_SPMM_PtrF.Sound = &m_soundManager;
		m_SPMM_PtrF.PhysicsEngine = &m_physicsEngine;
		return true;
	}

	void GameEngine::Release()
	{
		m_scenePluginManagerMoteur.Release();
		m_physicsEngine.Release();
		m_soundManager.Release();
		m_inputManager.Release();
		m_settingManager.Release();
		m_renderingEngine.Release();
		m_time.Release();
		Debug::Info("Liberation Moteur");
	}

	void GameEngine::Start()
	{
		Debug::Info("Moteur Start");
		m_time.StartTime();
		m_scenePluginManagerMoteur.SetDllPointeurF(m_SPMM_PtrF);
		m_scenePluginManagerDLL->LoadEntryScene();
		GameEngine::Update();
	}

	void GameEngine::Update()
	{
		while (!glfwWindowShouldClose(m_VulkanMisc->str_VulkanDeviceMisc->str_window))/*gestion d'evenement lier a la fermeture de la fenetre via la croix */
		{
			glfwPollEvents();/*event de recuperation*/
			m_time.FixedUpdateTime();
			m_lag += m_time.getFixedDeltaTime();			
			m_scenePluginManagerDLL->OnPreUpdate();
			if (m_lag >= 1 / m_settingManager.GetFps())
			{
				m_time.UpdateTime();
				m_physicsEngine.Update(m_time.getDeltaTime());
				m_inputManager.UpdateAxis();
				m_scenePluginManagerDLL->OnGUI();
				m_renderingEngine.DrawFrame();
				m_scenePluginManagerDLL->OnPostUpdate();
				m_lag -= 1/m_settingManager.GetFps();
			}
		}
	}
}