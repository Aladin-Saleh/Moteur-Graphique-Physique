#ifndef __CAPS_SHADER_UNIFORM_BUFFER_DIVER__
#define __CAPS_SHADER_UNIFORM_BUFFER_DIVER__

#include "Debug.hpp"
#include "VulkanMisc.hpp"
#include "BufferManager.hpp"
#include "CameraManager.hpp"
#include "I_SettingManager.hpp"

namespace Ge
{
	struct UniformBufferDiver
	{
		alignas(16) glm::vec3 camPos;
		alignas(int) int maxLight;
		alignas(float) float u_time;
		alignas(float) float gamma;
		alignas(int) int indShadowLight;
	};
	class ShaderUBdiver
	{
	public:
		bool Initialize(VulkanMisc * vM, CameraManager * cm, I_SettingManager * sM);
		VkBuffer GetUniformBuffers();
		void UpdateUniformBufferDiver();
		void Release();
	private:
		UniformBufferDiver m_ubd{};
		VulkanMisc * vMisc;
		VmaBuffer m_vmaUniformBuffer;
		CameraManager * camM;
		I_SettingManager * settingM;
	};
}

#endif //!__CAPS_SHADER_UNIFORM_BUFFER_DIVER__