#ifndef __CAPS__DESCRIPTOR_SETS__
#define __CAPS__DESCRIPTOR_SETS__

#include "Debug.hpp"
#include <vector>
#include "VulkanMisc.hpp"
#include "Model_Manager.hpp"
#include "TextureManager.hpp"
#include "MaterialManager.hpp"
#include "LightManager.hpp"
#include "ShaderUBdiver.hpp"
#include "ShadowManager.hpp"

namespace Ge
{

	class DescriptorSets
	{
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanMisc * vM, Model_Manager * mM, TextureManager * tM, MaterialManager * mMat, LightManager * lM, ShaderUBdiver* suD, ShadowManager * sM);
		void Release(VulkanMisc * vM);
	private:
		std::vector<VkDescriptorSet> m_descriptorSets;
	};
}

#endif //!__CAPS__DESCRIPTOR_SETS__