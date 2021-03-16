#ifndef __CAPS_MODEL_BUFFER__
#define __CAPS_MODEL_BUFFER__

#include "VulkanMisc.hpp"
#include "BufferManager.hpp"
#include "ShapeBuffer.hpp"

namespace Ge
{
	class ModelBuffer : public ShapeBuffer
	{
	public:
		ModelBuffer(std::vector<Vertex> vertices, std::vector<uint32_t> indices, VulkanMisc * vM);
		~ModelBuffer();
		VkBuffer GetIndexBuffer();
		VkBuffer * GetVertexBuffer();
		VkDeviceSize GetDeviceSize();
		uint32_t GetIndiceSize();
		std::vector<Vertex> GetVertices();
		bool getDestroy();
		void Destroy();
	private:
		std::vector<Vertex> m_vertices;
		std::vector<uint32_t> m_indices;
		VkDevice device;
		VmaBuffer m_vmaIndexBuffer;
		VmaBuffer m_vmaVertexBuffer;
		VkDeviceSize m_bufferSize;
		uint32_t m_indiceSize;
		bool m_destroy = false;
	};
}

#endif // !__CAPS_MODEL_BUFFER__
