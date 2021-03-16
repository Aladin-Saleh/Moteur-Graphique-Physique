#include "ShaderUBdiver.hpp"
#include "Time.hpp"

namespace Ge
{
	bool ShaderUBdiver::Initialize(VulkanMisc * vM, CameraManager * cm, I_SettingManager * sM)
	{
		Debug::Info("Initialisation du Shader UBDiver");
		camM = cm;
		vMisc = vM;
		settingM = sM;
		if (!BufferManager::createBuffer(sizeof(UniformBufferDiver), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_vmaUniformBuffer, vM->str_VulkanDeviceMisc))
		{
			Debug::Error("Echec de la creation d'un uniform buffer Diver");
			return false;
		}
		return true;
	}

	VkBuffer ShaderUBdiver::GetUniformBuffers()
	{
		return m_vmaUniformBuffer.buffer;
	}

	void ShaderUBdiver::UpdateUniformBufferDiver()
	{		
		Vector3 pos = camM->getCurrentCamera()->getPosition();
		m_ubd.camPos = glm::vec3(pos.x, pos.y, pos.z);
		m_ubd.maxLight = vMisc->str_VulkanDescriptor->lightCount;
		m_ubd.u_time = Time::GetTime();
		m_ubd.gamma = settingM->GetGamma();
		m_ubd.indShadowLight = vMisc->str_VulkanDescriptor->shadowLightIndice;
		memcpy(BufferManager::mapMemory(m_vmaUniformBuffer), &m_ubd, sizeof(m_ubd));
		BufferManager::unMapMemory(m_vmaUniformBuffer);
	}

	void ShaderUBdiver::Release()
	{
		BufferManager::destroyBuffer(m_vmaUniformBuffer);
		Debug::Info("Liberation du Shader UBDiver");
	}
}
