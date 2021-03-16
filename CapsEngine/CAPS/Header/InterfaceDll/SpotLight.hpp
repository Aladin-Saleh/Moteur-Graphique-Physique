#ifndef __CAPS_INTERFACE_SPOT_LIGHT__
#define __CAPS_INTERFACE_SPOT_LIGHT__

#include "Light.hpp"

class SpotLight : virtual public Light
{
public:
	virtual float GetConstant() = 0;
	virtual void SetConstant(float constant) = 0;
	virtual float GetLinear() = 0;
	virtual void SetLinear(float linear) = 0;
	virtual float GetQuadratic() = 0;
	virtual void SetQuadratic(float quadratic) = 0;
	virtual float GetCutOff() = 0;
	virtual void SetCutOff(float cutOff) = 0;
	virtual float GetOuterCutOff() = 0;
	virtual void SetOuterCutOff(float outerCutOff) = 0;
};

#endif //!__CAPS_INTERFACE_SPOT_LIGHT__