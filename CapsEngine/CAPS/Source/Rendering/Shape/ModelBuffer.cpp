#include "ModelBuffer.hpp"

namespace Ge
{
	ModelBuffer::ModelBuffer(std::vector<Vertex> vertices, std::vector<uint32_t> indices, VulkanMisc * vM)
	{
		m_vertices = vertices;
		m_indices = indices;
		device = vM->str_VulkanDeviceMisc->str_device;
		m_bufferSize = sizeof(indices[0]) * indices.size();
		m_indiceSize = static_cast<uint32_t>(m_indices.size());

		VmaBuffer stagingBufferI;
		BufferManager::createBuffer(m_bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBufferI, vM->str_VulkanDeviceMisc);
		memcpy(BufferManager::mapMemory(stagingBufferI), indices.data(), (size_t)m_bufferSize);
		BufferManager::unMapMemory(stagingBufferI);
		BufferManager::createBuffer(m_bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_vmaIndexBuffer, vM->str_VulkanDeviceMisc);
		BufferManager::copyBuffer(stagingBufferI.buffer, m_vmaIndexBuffer.buffer, m_bufferSize, vM);
		BufferManager::destroyBuffer(stagingBufferI);

		m_bufferSize = sizeof(vertices[0]) * vertices.size();

		VmaBuffer stagingBufferV;
		BufferManager::createBuffer(m_bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBufferV, vM->str_VulkanDeviceMisc);

		memcpy(BufferManager::mapMemory(stagingBufferV), m_vertices.data(), (size_t)m_bufferSize);
		BufferManager::unMapMemory(stagingBufferV);

		BufferManager::createBuffer(m_bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_vmaVertexBuffer, vM->str_VulkanDeviceMisc);
		BufferManager::copyBuffer(stagingBufferV.buffer, m_vmaVertexBuffer.buffer, m_bufferSize, vM);
		BufferManager::destroyBuffer(stagingBufferV);
	}

	ModelBuffer::~ModelBuffer()
	{
		BufferManager::destroyBuffer(m_vmaIndexBuffer);
		BufferManager::destroyBuffer(m_vmaVertexBuffer);
	}

	VkBuffer ModelBuffer::GetIndexBuffer()
	{
		return m_vmaIndexBuffer.buffer;
	}

	VkBuffer * ModelBuffer::GetVertexBuffer()
	{
		return &m_vmaVertexBuffer.buffer;
	}

	VkDeviceSize ModelBuffer::GetDeviceSize()
	{
		return m_bufferSize;
	}

	uint32_t ModelBuffer::GetIndiceSize()
	{
		return m_indiceSize;
	}

	std::vector<Vertex> ModelBuffer::GetVertices()
	{
		return m_vertices;
	}

	bool ModelBuffer::getDestroy()
	{
		return m_destroy;
	}

	void ModelBuffer::Destroy()
	{
		m_destroy = true;
	}
}