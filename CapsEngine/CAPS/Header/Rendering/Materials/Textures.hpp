#ifndef __CAPS_TEXTURES__
#define __CAPS_TEXTURES__

#include "stb-cmake/stb_image.h"
#include "VulkanMisc.hpp"
#include "BufferManager.hpp"
#include "Texture.hpp"

namespace Ge
{
	class Textures : public Texture
	{
	public:
		Textures(stbi_uc* pc, int Width,int Height,int index, VulkanMisc * vM);
		~Textures();
		VkImageView getVkImageView();
		VkSampler getVkSampler();
		int getIndex();
		void setIndex(int i);
		void Destroy();
		bool getDestroy();
	private:
		static void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels, VulkanMisc * vM);
		static void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels, VulkanMisc * vM);
	private:
		int texWidth, texHeight;
		stbi_uc* pixelContainer;
		uint32_t mipLevels;
		float minLod = 0.0f;
		VmaBufferImage textureImage;
		VkDeviceSize imageSize;	
		VkImageView textureImageView;
		VkSampler textureSampler;
		VulkanDeviceMisc * vMD;
		int index = 0;
		bool m_destroy = false;
	};
}

#endif // !__CAPS_TEXTURES__
