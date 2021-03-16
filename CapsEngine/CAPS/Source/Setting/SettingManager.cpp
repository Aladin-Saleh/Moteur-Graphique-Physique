#include "SettingManager.hpp"

namespace Ge
{
	bool SettingManager::Initialize(ptrF * ptrf)
	{
		ptrf->Setting = this;
		m_settingInfo.m_gamma = 1.0f;
		Debug::Info("Initialisation des parametres");
		return true;
	}
	void SettingManager::Release()
	{
		Debug::Info("Liberation des parametres");
	}

	double SettingManager::GetFps()
	{
	
			return m_settingInfo.m_fps;
	}


	void SettingManager::SetFps(double fps)
	{
		
		m_settingInfo.m_fps = fps;
		
	}


	const char * SettingManager::GetName()
	{
		return m_settingInfo.m_name;
	}


	void SettingManager::SetName(const char* name)
	{
		
		m_settingInfo.m_name = name;
		
	}
	double SettingManager::GetWindowHeight()
	{
		
			return m_settingInfo.m_sizeHeightWindow;
		
	}

	void SettingManager::SetWindowHeight(double height)
	{
		
		m_settingInfo.m_sizeHeightWindow = height;
			
	
	}

	double SettingManager::GetWindowWidth()
	{
		
			return m_settingInfo.m_sizeWidthWindow;
		
	}
	void SettingManager::SetWindowWidth(double Width)
	{
		
		m_settingInfo.m_sizeWidthWindow = Width;
		
	}
	Vector3 SettingManager::GetGravity()
	{
		
			return m_settingInfo.m_gravity;
		
	}
	void SettingManager::SetGravity(Vector3 gravity)
	{
		
		m_settingInfo.m_gravity = gravity;
	
	}
	void SettingManager::SetVersion(version v)
	{
		
		m_settingInfo.m_version = v;

	}

	version SettingManager::GetVersion()
	{
			return m_settingInfo.m_version;
		
	}

	void SettingManager::SetClearColor(Vector4 color)
	{
		m_settingInfo.m_clearColor = color;
	}

	Vector4 SettingManager::GetClearColor()
	{
		return m_settingInfo.m_clearColor;
	}

	void SettingManager::SetGamma(float gamma)
	{
		m_settingInfo.m_gamma = gamma;
	}

	float SettingManager::GetGamma()
	{
		return m_settingInfo.m_gamma;
	}
}