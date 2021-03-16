#ifndef __CAPS_SPOT_LIGHT__
#define __CAPS_SPOT_LIGHT__

#include "SpotLight.hpp"
#include "Lights.hpp"

namespace Ge
{
	class LSpot : public Lights, public SpotLight
	{
	public:
		LSpot(int index, VulkanMisc * vM);
		float GetConstant();
		void SetConstant(float constant);
		float GetLinear();
		void SetLinear(float linear);
		float GetQuadratic();
		void SetQuadratic(float quadratic);
		float GetCutOff();
		void SetCutOff(float cutOff);
		float GetOuterCutOff();
		void SetOuterCutOff(float outerCutOff);
	};
}

#endif //!__CAPS_SPOT_LIGHT__