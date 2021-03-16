#include "TextureManager.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb-cmake/stb_image.h"

namespace Ge
{
	bool TextureManager::Intialize(VulkanMisc * vulkanMisc)
	{
		vM = vulkanMisc;
		nullTexture = TextureManager::CreateTexture("../TextureTest/null.png");
		if (!nullTexture)
		{
			Debug::Error("Echec du chargement de la Texture null");
			return false;
		}
		Debug::Info("Intialisation du TextureManager");
		return true;
	}

	void TextureManager::Release()
	{
		for (int i = 0; i < m_textures.size(); i++)
		{
			delete(m_textures[i]);
		}
		m_textures.clear();
		Debug::Info("Liberation du TextureManager");
	}

	Texture * TextureManager::CreateTexture(const char * path)
	{
		//vM->str_VulkanInfo->texture_info_name.push_back(path);
		int tw, th, tc;
		stbi_uc* pixel = stbi_load(path, &tw, &th, &tc, STBI_rgb_alpha);
		if (!pixel)
		{
			Debug::Warn("Echec du chargement de la texture");
			return nullptr;
		}
		Textures * texture = new Textures(pixel, tw, th, m_textures.size(), vM);
		m_textures.push_back(texture);
		stbi_image_free(pixel);
		vM->str_VulkanDescriptor->TextureCount = m_textures.size();
		return (Texture *)texture;
	}

	void TextureManager::DestroyTexture(Texture * texture)
	{
		for (int i = 0; i < m_textures.size(); i++)
		{
			if ((Texture *)m_textures[i] == texture)
			{
				m_textures[i]->Destroy();
			}
		}
		m_recreateDescripteur = true;
		m_destroy = true;
	}

	void TextureManager::DestroyTextures()
	{
		Textures * texture;
		for (int i = 0; i < m_textures.size(); i++)
		{
			if (m_textures[i]->getDestroy())
			{
				texture = m_textures[i];
				m_textures.erase(m_textures.begin() + i);
				delete(texture);
			}
		}
		vM->str_VulkanDescriptor->TextureCount = m_textures.size();
		majIndex();
	}

	std::vector<Textures*> TextureManager::getTextures()
	{
		return m_textures;
	}

	Texture * TextureManager::getNullTextures()
	{
		return nullTexture;
	}

	Textures * TextureManager::getNTextures()
	{
		return m_textures[0];
	}

	bool TextureManager::recreateDescripteurTextures()
	{
		bool buf = m_recreateDescripteur;
		m_recreateDescripteur = false;
		return buf;
	}

	bool TextureManager::destoyTexturesState()
	{
		bool buf = m_destroy;
		m_destroy = false;
		return buf;
	}

	void TextureManager::majIndex()
	{
		for (int i = 0; i < m_textures.size(); i++)
		{
			m_textures[i]->setIndex(i);
		}
	}
}