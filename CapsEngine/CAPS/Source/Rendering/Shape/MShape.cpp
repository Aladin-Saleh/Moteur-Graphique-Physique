#include "MShape.hpp"

namespace Ge
{
	MShape::MShape(ModelBuffer * buffer, int indexubo, VulkanMisc * vM) : GObject()
	{
		vMisc = vM;
		m_buffer = buffer;
		m_device = vM->str_VulkanDeviceMisc->str_device;
		m_material = nullptr;

		if (!BufferManager::createBuffer(sizeof(UniformBufferObject), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_vmaUniformBuffer, vM->str_VulkanDeviceMisc)) 
		{
			Debug::Error("Echec de la creation d'un uniform buffer object");
		}
		m_index.ubo = indexubo;
		m_index.material = 0;
	}

	MShape::~MShape()
	{
		BufferManager::destroyBuffer(m_vmaUniformBuffer);
	}

	void MShape::Render(VkCommandBuffer CmdBuffer, VkDescriptorSet pDescriptorSets, VkPipelineLayout pipelineLayout, VkShaderStageFlags pushConstantShaderFlags)
	{
		//vkCmdBindPipeline(CmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(CmdBuffer, 0, 1, m_buffer->GetVertexBuffer(), offsets);

		vkCmdBindIndexBuffer(CmdBuffer, m_buffer->GetIndexBuffer(), 0, VK_INDEX_TYPE_UINT32);

		vkCmdBindDescriptorSets(CmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &pDescriptorSets, 0, nullptr);
		
		vkCmdPushConstants(
			CmdBuffer,
			pipelineLayout,
			pushConstantShaderFlags,
			0,
			sizeof(PushConstants),
			&m_index);

		vkCmdDrawIndexed(CmdBuffer, m_buffer->GetIndiceSize(), 1, 0, 0, 0);
	}

	void MShape::UpdateUniformBufferObject(Camera * cam)
	{
		m_ubo.model = m_transform.translateMatrix * m_transform.rotationMatrix;
		m_ubo.model = glm::scale(m_ubo.model, m_transform.scale);

		m_ubo.view = cam->getView();
		m_ubo.proj = cam->getProjection();

		memcpy(BufferManager::mapMemory(m_vmaUniformBuffer), &m_ubo, sizeof(m_ubo));
		BufferManager::unMapMemory(m_vmaUniformBuffer);
	}

	void MShape::SetMaterial(Material * material)
	{
		if (material)
		{
			removeComponent(m_material);
			m_material = material;
			m_index.material = m_material->GetIndex();
			addComponent(m_material);
			vMisc->str_VulkanCommandeBufferMisc->str_recreate = true;
		}
		else
		{
			Debug::Warn("Material nullptr");
		}
	}

	Material * MShape::GetMaterial()
	{
		return m_material;
	}

	VkBuffer MShape::GetUniformBuffers()
	{
		return m_vmaUniformBuffer.buffer;
	}

	ModelBuffer * MShape::getModelBuffer()
	{
		return m_buffer;
	}

	void MShape::SetTag(std::string tag)
	{
		m_tag = tag;
	}

	std::string MShape::GetTag()
	{
		return m_tag;
	}

	void MShape::Destroy()
	{
		m_destroy = true;
	}

	bool MShape::getDestroy()
	{
		return m_destroy;
	}

	UniformBufferObject MShape::getUBO()
	{
		return m_ubo;
	}

	void MShape::setIndexUbo(int index)
	{
		m_index.ubo = index;
	}

	void MShape::MajTexture()
	{
		if (!m_material)
		{
			m_index.material = 0;
			return;
		}
		m_index.material = m_material->GetIndex();
	}
}
