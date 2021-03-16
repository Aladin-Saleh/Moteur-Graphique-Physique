#include "Lights.hpp"

namespace Ge
{
	Lights::Lights(int index, VulkanMisc * vM) : GObject()
	{
		vMisc = vM;
		m_index = index;
		m_ubl.position = glm::vec3(0, 0, 0);
		m_ubl.diffuse = glm::vec3(0, 0, 0);
		m_ubl.specular = glm::vec3(0.0f);
		m_ubl.ambient = glm::vec3(0.1f);
		if (!BufferManager::createBuffer(sizeof(UniformBufferLight), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_vmaUniformBuffer, vM->str_VulkanDeviceMisc))
		{
			Debug::Error("Echec de la creation d'un uniform buffer object");
		}
		if (!BufferManager::createBuffer(sizeof(OffScreenShadow), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_vmaOffScreenShadowBuffer, vM->str_VulkanDeviceMisc))
		{
			Debug::Error("Echec de la creation d'un uniform buffer object");
		}
		UpdateLightSpaceMatrix();
	}

	void Lights::SetColors(Vector3 color)
	{
		m_ubl.diffuse = glm::vec3(color.x, color.y, color.z);
	}

	Vector3 Lights::GetColors()
	{
		return Vector3(m_ubl.diffuse.x, m_ubl.diffuse.y, m_ubl.diffuse.z);
	}

	void Lights::SetSpecular(Vector3 spec)
	{
		m_ubl.specular = glm::vec3(spec.x, spec.y, spec.z);
	}

	Vector3 Lights::GetSpecular()
	{
		return Vector3(m_ubl.specular.x, m_ubl.specular.y, m_ubl.specular.z);
	}

	Vector3 Lights::GetDirection()
	{
		return Vector3(m_ubl.direction.x, m_ubl.direction.y, m_ubl.direction.z);
	}

	void Lights::SetDirection(Vector3 direction)
	{
		m_ubl.direction = glm::vec3(direction.x, direction.y, direction.z);
		m_transform.eul = direction;//A changer
		m_transform.eulerAngles = m_ubl.direction;//A changer
		UpdateLightSpaceMatrix();
	}

	void Lights::setEulerAngles(Vector3 eul)
	{
		m_ubl.direction = glm::vec3(eul.x, eul.y, eul.z);
		m_transform.eul = eul;//A changer
		m_transform.eulerAngles = m_ubl.direction;//A changer
		UpdateLightSpaceMatrix();
	}

	Vector3 Lights::getEulerAngles()
	{
		return m_transform.eul;
	}

	Vector3 Lights::getPosition()
	{
		return Vector3(m_ubl.position.x, m_ubl.position.y, m_ubl.position.z);
	}

	void Lights::setPosition(Vector3 position)
	{
		m_ubl.position = glm::vec3(position.x, position.y, position.z);
		m_transform.position = m_ubl.position;
		m_transform.pos = position;
		UpdateLightSpaceMatrix();
	}

	void Lights::SetAmbiant(Vector3 ambiant)
	{
		m_ubl.ambient = glm::vec3(ambiant.x, ambiant.y, ambiant.z);
	}

	void Lights::SetShadow(bool state)
	{
		m_shadow = state;
		if (m_shadow)
		{
			vMisc->str_VulkanDescriptor->shadowLightIndice = m_index;
		}
		else
		{
			vMisc->str_VulkanDescriptor->shadowLightIndice = 0;
		}
		UpdateLightSpaceMatrix();
	}

	int Lights::GetStatus()
	{
		return m_ubl.status;
	}

	Vector3 Lights::GetAmbiant()
	{
		return Vector3(m_ubl.ambient.x, m_ubl.ambient.y, m_ubl.ambient.z);
	}

	int Lights::GetIndex()
	{
		return m_index;
	}

	void Lights::SetIndex(int i)
	{
		m_index = i;
		if (m_shadow)
		{
			vMisc->str_VulkanDescriptor->shadowLightIndice = m_index;
		}
	}

	VkBuffer Lights::GetUniformBuffers()
	{
		return m_vmaUniformBuffer.buffer;
	}

	VkBuffer Lights::GetlightMatrixShadowUniformBuffers()
	{
		return m_vmaOffScreenShadowBuffer.buffer;
	}

	void Lights::UpdateLightSpaceMatrix()
	{
		glm::mat4 lightProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 300.0f);
		glm::mat4 lightView = glm::lookAt(m_ubl.position,glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 lightSpaceMatrix = lightProjection * lightView;
	
		m_ubl.lightSpaceMatrix = lightSpaceMatrix;
		m_uboOffscreenVS.lightSpaceMatrix = lightSpaceMatrix;

		memcpy(BufferManager::mapMemory(m_vmaOffScreenShadowBuffer), &m_uboOffscreenVS, sizeof(m_uboOffscreenVS));
		BufferManager::unMapMemory(m_vmaOffScreenShadowBuffer);
	}

	void Lights::UpdateUniformBufferLight()
	{
		memcpy(BufferManager::mapMemory(m_vmaUniformBuffer), &m_ubl, sizeof(m_ubl));
		BufferManager::unMapMemory(m_vmaUniformBuffer);
	}

	void Lights::OnGUI()
	{
		m_imGUiUBL.ambient[0] = m_ubl.ambient.x;
		m_imGUiUBL.ambient[1] = m_ubl.ambient.y;
		m_imGUiUBL.ambient[2] = m_ubl.ambient.z;

		m_imGUiUBL.diffuse[0] = m_ubl.diffuse.x;
		m_imGUiUBL.diffuse[1] = m_ubl.diffuse.y;
		m_imGUiUBL.diffuse[2] = m_ubl.diffuse.z;

		m_imGUiUBL.specular[0] = m_ubl.specular.x;
		m_imGUiUBL.specular[1] = m_ubl.specular.y;
		m_imGUiUBL.specular[2] = m_ubl.specular.z;

		GObject::OnGUI();
		ImGui::TextColored(ImVec4(0.2f, 1, 0.2f, 1), "Light\n");
		if (ImGui::ColorEdit3("Color", m_imGUiUBL.diffuse))
		{
			SetColors(Vector3(m_imGUiUBL.diffuse[0], m_imGUiUBL.diffuse[1], m_imGUiUBL.diffuse[2]));
		}
		if (ImGui::ColorEdit3("Ambiant", m_imGUiUBL.ambient))
		{
			SetAmbiant(Vector3(m_imGUiUBL.ambient[0], m_imGUiUBL.ambient[1], m_imGUiUBL.ambient[2]));
		}
		if (ImGui::ColorEdit3("Specular", m_imGUiUBL.specular))
		{
			SetSpecular(Vector3(m_imGUiUBL.specular[0], m_imGUiUBL.specular[1], m_imGUiUBL.specular[2]));
		}
		ImGui::DragFloat("Quadratic", &m_ubl.quadratic,0.1f);
		ImGui::DragFloat("Constant", &m_ubl.constant,0.1f);
		ImGui::DragFloat("Linear", &m_ubl.linear,0.1f);
		if (m_ubl.status == 2)
		{
			ImGui::DragFloat("CutOff", &m_ubl.cutOff,0.2f);
			ImGui::DragFloat("OuterCutOff", &m_ubl.outerCutOff,0.2f);
		}
	}

	Lights::~Lights()
	{
		BufferManager::destroyBuffer(m_vmaOffScreenShadowBuffer);
		BufferManager::destroyBuffer(m_vmaUniformBuffer);
	}
}