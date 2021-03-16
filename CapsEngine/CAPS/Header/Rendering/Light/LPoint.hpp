#ifndef __CAPS_POINT_LIGHT__
#define __CAPS_POINT_LIGHT__

#include "PointLight.hpp"
#include "Lights.hpp"

namespace Ge
{
	class LPoint : public Lights, public PointLight
	{
	public:
		LPoint(int index, VulkanMisc * vM);
		float GetConstant();
		void SetConstant(float constant);
		float GetLinear();
		void SetLinear(float linear);
		float GetQuadratic();
		void SetQuadratic(float quadratic);
	};
}

#endif //!__CAPS_POINT_LIGHT__