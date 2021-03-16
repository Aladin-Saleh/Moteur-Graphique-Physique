#include "LightManager.hpp"

namespace Ge
{
	bool LightManager::Initialize(VulkanMisc * vM)
	{
		vulkanM = vM;
		DirectionalLight * dl = CreateDirectionalLight(Vector3(0.0f), Vector3(0.f));
		if (!m_shadowManager.Initialize(vM))
		{
			Debug::Error("Erreur l'ors de l'initialisation de shadow map");
			return false;
		}
		Debug::Info("Initialisation du Light Manager");
		return true;
	}

	std::vector<Lights*> LightManager::GetLights()
	{
		return m_lights;
	}

	SpotLight * LightManager::CreateSpotLight(Vector3 position, Vector3 color, Vector3 direction, float cutOff, float outerCutOff, std::string name)
	{
		LSpot * light = new LSpot(m_lights.size(), vulkanM);
		light->setPosition(position);
		light->SetColors(color);
		light->SetDirection(direction);
		light->SetCutOff(cutOff);
		light->SetOuterCutOff(outerCutOff);
		light->setName(name);
		m_lights.push_back((Lights *)light);
		m_MapLights[(Light *)light] = light;
		vulkanM->str_VulkanDescriptor->lightCount = m_lights.size();
		return (SpotLight *)light;
	}

	DirectionalLight * LightManager::CreateDirectionalLight(Vector3 direction, Vector3 color, std::string name)
	{
		LDirectional * light = new LDirectional(m_lights.size(), vulkanM);
		light->SetColors(color);
		light->SetDirection(direction);
		light->setName(name);
		m_lights.push_back((Lights *)light);
		m_MapLights[(Light *)light] = light;
		vulkanM->str_VulkanDescriptor->lightCount = m_lights.size();
		return (DirectionalLight *)light;
	}

	PointLight * LightManager::CreatePointLight(Vector3 position, Vector3 color, std::string name)
	{
		LPoint * light = new LPoint(m_lights.size(), vulkanM);
		light->setPosition(position);
		light->SetColors(color);	
		light->setName(name);
		m_lights.push_back((Lights *)light);
		m_MapLights[(Light *)light] = light;
		vulkanM->str_VulkanDescriptor->lightCount = m_lights.size();
		return (PointLight *)light;
	}

	void LightManager::DestroyLight(Light * light)
	{
		Lights * li;
		li = m_MapLights[light];
		m_MapLights.erase(light);
		m_lights.erase(m_lights.begin() + li->GetIndex());		
		delete(li);
		vulkanM->str_VulkanDescriptor->lightCount = m_lights.size();
		MajIndex();
	}

	void LightManager::UpdateUniformBufferLight()
	{
		for (Lights * light : m_lights)
		{
			light->UpdateUniformBufferLight();
		}
	}

	void LightManager::Release()
	{
		for (Lights * light : m_lights)
		{
			delete(light);
		}
		m_lights.clear();
		m_MapLights.clear();
		vulkanM->str_VulkanDescriptor->lightCount = 0;
		m_shadowManager.Release();
		Debug::Info("Liberation du light Manager");
	}

	void LightManager::MajIndex()
	{
		for (int i = 0; i < m_lights.size(); i++)
		{
			m_lights[i]->SetIndex(i);
		}
	}

	ShadowManager * LightManager::GetShadowManager()
	{
		return &m_shadowManager;
	}
}