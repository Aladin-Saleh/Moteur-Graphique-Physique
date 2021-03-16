#ifndef __CAPS_LIGHT_MANAGER__
#define __CAPS_LIGHT_MANAGER__

#include "I_LightManager.hpp"
#include "VulkanMisc.hpp"
#include "Lights.hpp"
#include "LSpot.hpp"
#include "LDirectional.hpp"
#include "LPoint.hpp"
#include "Debug.hpp"
#include <map>
#include "ShadowManager.hpp"

namespace Ge
{
	class LightManager : public I_LightManager
	{
	private:
		friend class RenderingEngine;
		bool Initialize(VulkanMisc * vM);
		void Release();
		void MajIndex();
		ShadowManager * GetShadowManager();
	public:
		std::vector<Lights*> GetLights();
		SpotLight * CreateSpotLight(Vector3 position, Vector3 color, Vector3 direction, float cutOff, float outerCutOff, std::string name = "SpotLight");
		DirectionalLight * CreateDirectionalLight(Vector3 direction, Vector3 color, std::string name = "DirectionalLight");
		PointLight * CreatePointLight(Vector3 position, Vector3 color, std::string name = "PointLight");
		void DestroyLight(Light * light);
		void UpdateUniformBufferLight();
	private:
		std::map<Light *, Lights *> m_MapLights;
		std::vector<Lights*> m_lights;
		VulkanMisc * vulkanM;
		ShadowManager m_shadowManager;
	};
}

#endif // !__CAPS_LIGHT_MANAGER__
