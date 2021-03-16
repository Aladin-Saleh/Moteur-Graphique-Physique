#ifndef __CAPS_TEXTURE_MANAGER__
#define __CAPS_TEXTURE_MANAGER__

#include "VulkanMisc.hpp"
#include "Textures.hpp"
#include "Debug.hpp"
#include "I_TextureManager.hpp"

namespace Ge
{
	class TextureManager : public I_TextureManager
	{
	private:
		friend class RenderingEngine;
		bool Intialize(VulkanMisc * vM);
		void Release();
	public:
		Texture * CreateTexture(const char * path);
		void DestroyTexture(Texture * texture);
		void DestroyTextures();
		std::vector<Textures *> getTextures();
		Texture * getNullTextures();
		Textures * getNTextures();
		bool recreateDescripteurTextures();
		bool destoyTexturesState();
	private:
		void majIndex();
	private:
		VulkanMisc * vM;
		std::vector<Textures *> m_textures;
		Texture * nullTexture;
		bool m_recreateDescripteur = false;
		bool m_destroy = false;
	};
}

#endif // !__CAPS_TEXTURE_MANAGER__
