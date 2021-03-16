#ifndef __CAPS_MATERIAL_MANAGER__
#define __CAPS_MATERIAL_MANAGER__

#include "I_MaterialManager.hpp"
#include "VulkanMisc.hpp"
#include "Materials.hpp"
#include "Debug.hpp"
#include <map>

namespace Ge
{
	class MaterialManager : public I_MaterialManager
	{
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanMisc * vM);
		void Release();
		void MajIndex();
	public:
		std::vector<Materials *> GetMaterial();
		Material * AllocateMaterial();
		void DestroyMaterial(Material * material);
		bool recreateDescripteurMaterial();
		void UpdateUniformBufferObject();
		Materials * GetBaseMaterial();
	private:
		std::map<Material *, Materials *> m_MapMaterials;
		std::vector<Materials *> m_materials;
		VulkanMisc * vulkanM;
		bool m_recreateDescripteur = false;
	};
}

#endif // !__CAPS_MATERIAL_MANAGER__
