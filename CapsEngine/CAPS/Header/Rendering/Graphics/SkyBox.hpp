#ifndef __CAPS_SKYBOX__
#define __CAPS_SKYBOX__

#include "Debug.hpp"
#include "VulkanMisc.hpp"

namespace Ge
{
	class SkyBox
	{
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanMisc * vM);
		void Render(VulkanMisc * vM,uint32_t currentframe);
		void Release(VkDevice device);
	private:
		VkPipeline m_graphicsPipelineSkybox;
		//std::vector<>
	};

}

#endif //!__CAPS_SKYBOX__