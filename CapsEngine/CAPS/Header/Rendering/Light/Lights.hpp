#ifndef __CAPS_LIGHT__
#define __CAPS_LIGHT__

#include "Light.hpp"
#include "Vector3.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/common.hpp"
#include "Debug.hpp"
#include "VulkanMisc.hpp"
#include "BufferManager.hpp"
#include "GObject.hpp"

namespace Ge
{
	struct UniformBufferLight
	{
		alignas(16) glm::vec3 position;
		alignas(16) glm::vec3 direction;
		alignas(float) float cutOff;
		alignas(float) float outerCutOff;

		alignas(float) float constant;
		alignas(float) float linear;
		alignas(float) float quadratic;

		alignas(16) glm::vec3 ambient;
		alignas(16) glm::vec3 diffuse;
		alignas(16) glm::vec3 specular;
		alignas(int) int status;//DirLight = 0 ; PointLight = 1 ; SpotLight = 2
		alignas(16) glm::mat4 lightSpaceMatrix;
	};

	struct ImGUiUBL
	{
		float ambient[3];
		float diffuse[3];
		float specular[3];
	};

	struct OffScreenShadow{
		alignas(16) glm::mat4 lightSpaceMatrix;
	};

	class Lights : virtual public Light, public GObject
	{
	public:
		Lights(int index, VulkanMisc * vM);
		void SetColors(Vector3 color);
		Vector3 GetColors();
		void SetSpecular(Vector3 spec);
		Vector3 GetSpecular();
		Vector3 GetDirection();
		void SetDirection(Vector3 direction);
		void setEulerAngles(Vector3 eul) override;
		Vector3 getEulerAngles() override;
		Vector3 getPosition() override;
		void setPosition(Vector3 pos) override;
		void SetAmbiant(Vector3 ambiant);
		void SetShadow(bool  state);
		int GetStatus();
		Vector3 GetAmbiant();
		int GetIndex();
		void SetIndex(int i);
		VkBuffer GetUniformBuffers();
		VkBuffer GetlightMatrixShadowUniformBuffers();
		void UpdateLightSpaceMatrix();
		void UpdateUniformBufferLight();
		void OnGUI() override;
		virtual ~Lights();
	protected:
		friend class LSpot;
		UniformBufferLight m_ubl{};
		ImGUiUBL m_imGUiUBL{};
		OffScreenShadow m_uboOffscreenVS;
		VulkanMisc * vMisc;
		VmaBuffer m_vmaUniformBuffer;
		VmaBuffer m_vmaOffScreenShadowBuffer;
		float m_nearPlane = 1.0f;
		float m_farPlane = 7.5f;
		int m_index = 0;
		bool m_destroy = false;
		bool m_shadow = false;
	};
}

#endif // !__CAPS_LIGHT__
