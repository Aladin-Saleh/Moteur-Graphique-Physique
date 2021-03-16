#ifndef __CAPS_MATERIALS__
#define __CAPS_MATERIALS__

#include "Material.hpp"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "glm/glm.hpp"
#include "Textures.hpp"
#include "Debug.hpp"
#include "VulkanMisc.hpp"
#include "BufferManager.hpp"
#include "imgui-cmake/Header/imgui.h"

namespace Ge
{
	struct UniformBufferMaterial
	{
		alignas(16) glm::vec3 albedo;
		alignas(16) glm::vec2 offset;
		alignas(float) float metallic;
		alignas(float) float hdr;
		alignas(float) float normal;
		alignas(float) float ao;
		alignas(int) int albedoMap;
		alignas(int) int normalMap;
		alignas(int) int metallicMap;
		alignas(int) int hdrMap;
		alignas(int) int aoMap;
		alignas(bool) bool light;
	};
	class Materials : public Material
	{
	public:
		Materials(int index, VulkanMisc * vM);
		void SetColor(Vector3 color);
		void SetMetallic(float metal);
		void SetHDR(float hdr);
		void SetNormal(float normal);
		void SetOclusion(float ao);
		void SetAlbedoTexture(Texture * albedo);
		void SetNormalTexture(Texture * normal);
		void SetMetallicTexture(Texture * metal);
		void SetHDRTexture(Texture * hdr);
		void SetOclusionTexture(Texture * oclu);
		Vector3 GetColor();
		float GetMetallic();
		float GetHDR();
		float GetNormal();
		float GetOclusion();
		Texture * GetAlbedoTexture();
		Texture * GetNormalTexture();
		Texture * GetMetallicTexture();
		Texture * GetHDRTexture();
		Texture * GetOclusionTexture();
		VkBuffer GetUniformBuffers();
		void UpdateUniformBufferMaterial();
		int GetIndex();
		void SetIndex(int i);
		void MajTextureIndex();
		bool GetLightActive();
		void SetLightActive(bool state);
		Vector2 GetOffset();
		void SetOffset(Vector2 off);
		void OnGUI();
		~Materials();
	private:
		UniformBufferMaterial m_ubm{};
		VulkanMisc * vMisc;
		VmaBuffer m_vmaUniformBuffer;
		Texture * m_albedoMap;
		Texture * m_normalMap;
		Texture * m_metallicMap;
		Texture * m_hdrMap;
		Texture * m_aoMap;
		float m_color[3];
		float m_offset[2];
		int m_index = 0;
		bool m_destroy = false;
	};
}

#endif//!__CAPS_MATERIALS__