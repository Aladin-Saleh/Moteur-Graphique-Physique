#include "Materials.hpp"

namespace Ge
{
	Materials::Materials(int index, VulkanMisc * vM)
	{
		vMisc = vM;
		m_ubm.albedo = glm::vec3(1.0f, 1.0f, 1.0f);
		m_color[0] = m_ubm.albedo.x;
		m_color[1] = m_ubm.albedo.y;
		m_color[2] = m_ubm.albedo.z;
		m_ubm.metallic = 8.0f;
		m_ubm.normal = 1.0f;
		m_ubm.hdr = 1.0f;
		m_ubm.ao = 1.0f;
		m_ubm.albedoMap = 0;
		m_ubm.metallicMap = 0;
		m_ubm.aoMap = 0;
		m_ubm.normalMap = 0;
		m_ubm.hdrMap = 0;
		m_ubm.light = true;
		m_ubm.offset = glm::vec2(1.0f);
		m_offset[0] = m_ubm.offset.x;
		m_offset[1] = m_ubm.offset.y;

		if (!BufferManager::createBuffer(sizeof(UniformBufferMaterial), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_vmaUniformBuffer, vM->str_VulkanDeviceMisc))
		{
			Debug::Error("Echec de la creation d'un uniform buffer object");
		}

		m_index = index;
	}

	void Materials::SetColor(Vector3 color)
	{
		m_color[0] = color.x;
		m_color[1] = color.y;
		m_color[2] = color.z;
		m_ubm.albedo = glm::vec3(color.x, color.y, color.z);
	}

	void Materials::SetMetallic(float metal)
	{
		m_ubm.metallic = metal;
	}

	void Materials::SetHDR(float roug)
	{
		m_ubm.hdr = roug;
	}

	void Materials::SetNormal(float normal)
	{
		m_ubm.normal = normal;
	}

	void Materials::SetOclusion(float ao)
	{
		m_ubm.ao = ao;
	}

	void Materials::SetAlbedoTexture(Texture * albedo)
	{
		if (albedo)
		{
			m_ubm.albedoMap = albedo->getIndex();
			m_albedoMap = albedo;
		}		
	}

	void Materials::SetNormalTexture(Texture * normal)
	{
		if (normal)
		{
			m_ubm.normalMap = normal->getIndex();
			m_normalMap = normal;
		}
	}

	void Materials::SetMetallicTexture(Texture * metal)
	{
		if (metal)
		{
			m_ubm.metallicMap = metal->getIndex();
			m_metallicMap = metal;
		}
	}

	void Materials::SetHDRTexture(Texture * hdr)
	{
		if (hdr)
		{
			m_ubm.hdr = hdr->getIndex();
			m_hdrMap = hdr;
		}
	}

	void Materials::SetOclusionTexture(Texture * oclu)
	{
		if (oclu)
		{
			m_ubm.aoMap = oclu->getIndex();
			m_aoMap = oclu;
		}
	}

	Vector3 Materials::GetColor()
	{
		return Vector3(m_ubm.albedo.x, m_ubm.albedo.y, m_ubm.albedo.z);
	}

	float Materials::GetMetallic()
	{
		return m_ubm.metallic;
	}

	float Materials::GetHDR()
	{
		return m_ubm.hdr;
	}

	float Materials::GetNormal()
	{
		return m_ubm.normal;
	}

	float Materials::GetOclusion()
	{
		return m_ubm.ao;
	}

	Texture * Materials::GetAlbedoTexture()
	{
		return m_albedoMap;
	}

	Texture * Materials::GetNormalTexture()
	{
		return m_normalMap;
	}

	Texture * Materials::GetMetallicTexture()
	{
		return m_metallicMap;
	}

	Texture * Materials::GetHDRTexture()
	{
		return m_hdrMap;
	}

	Texture * Materials::GetOclusionTexture()
	{
		return m_aoMap;
	}

	VkBuffer Materials::GetUniformBuffers()
	{
		return m_vmaUniformBuffer.buffer;
	}

	void Materials::UpdateUniformBufferMaterial()
	{
		memcpy(BufferManager::mapMemory(m_vmaUniformBuffer), &m_ubm, sizeof(m_ubm));
		BufferManager::unMapMemory(m_vmaUniformBuffer);
	}

	int Materials::GetIndex()
	{
		return m_index;
	}
	void Materials::SetIndex(int i)
	{
		m_index = i;
	}

	void Materials::MajTextureIndex()
	{
		if (m_albedoMap)
		{
			m_ubm.albedoMap = m_albedoMap->getIndex();
		}
		if (m_normalMap)
		{
			m_ubm.normalMap = m_normalMap->getIndex();
		}
		if (m_metallicMap)
		{
			m_ubm.metallicMap = m_metallicMap->getIndex();
		}
		if (m_hdrMap)
		{
			m_ubm.hdrMap = m_hdrMap->getIndex();
		}
		if (m_aoMap)
		{
			m_ubm.aoMap = m_aoMap->getIndex();
		}
	}

	bool Materials::GetLightActive()
	{
		return m_ubm.light;
	}

	void Materials::SetLightActive(bool state)
	{
		m_ubm.light = state;
	}

	Vector2 Materials::GetOffset()
	{
		return Vector2(m_ubm.offset.x, m_ubm.offset.y);
	}

	void Materials::SetOffset(Vector2 off)
	{
		m_ubm.offset.x = off.x;
		m_ubm.offset.y = off.y;
		m_offset[0] = m_ubm.offset.x;
		m_offset[1] = m_ubm.offset.y;
	}

	void Materials::OnGUI()
	{
		ImGui::TextColored(ImVec4(0.2f, 1, 0.2f, 1), "Material\n");
		if (ImGui::ColorEdit3("Albedo", m_color))
		{
			SetColor(Vector3(m_color[0], m_color[1], m_color[2]));
		}
		if (ImGui::DragFloat2("Offset", m_offset,0.2f))
		{
			SetOffset(Vector2(m_offset[0], m_offset[1]));
		}
		ImGui::DragFloat("Specular", &m_ubm.metallic,0.2f);
		ImGui::DragFloat("Normal", &m_ubm.normal, 0.2f);
		ImGui::DragFloat("HDR", &m_ubm.hdr, 0.2f);
		ImGui::DragFloat("AO", &m_ubm.ao, 0.2f);
	}

	Materials::~Materials()
	{
		BufferManager::destroyBuffer(m_vmaUniformBuffer);
	}
}