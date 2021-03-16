#ifndef __CAPS_BUFFER_MANAGER__
#define __CAPS_BUFFER_MANAGER__

#include "vk_mem_alloc.h"
#include "VulkanMisc.hpp"
#include "Debug.hpp"

namespace Ge
{
	struct VmaBuffer
	{
		VkBuffer buffer;
		VmaAllocation allocation;
	};
	struct VmaBufferImage
	{
		VkImage image;
		VmaAllocation allocation;
	};
	class BufferManager
	{
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanMisc * vM);
		void Release();
	public:
		static bool createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags flags, VmaBuffer & buffer, VulkanDeviceMisc * vM);
		static bool createImageBuffer(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VmaBufferImage& image, VulkanDeviceMisc * vM);
		static void destroyBuffer(VmaBuffer & buffer);
		static void destroyImageBuffer(VmaBufferImage & buffer);
		static void * mapMemory(VmaBuffer & buffer);
		static void unMapMemory(VmaBuffer & buffer);
		static void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VulkanMisc * vM);
		static void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VulkanMisc * vM);
	private:
		static BufferManager * s_pInstance;
		VmaAllocator m_allocator;
	};
}

#endif // !__CAPS_BUFFER_MANAGER__
