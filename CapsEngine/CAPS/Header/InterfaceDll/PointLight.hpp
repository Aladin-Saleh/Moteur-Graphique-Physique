#ifndef __CAPS_INTERFACE_POINT_LIGHT__
#define __CAPS_INTERFACE_POINT_LIGHT__

#include "Light.hpp"

class PointLight : virtual public Light
{
public:
	virtual float GetConstant() = 0;
	virtual void SetConstant(float constant) = 0;
	virtual float GetLinear() = 0;
	virtual void SetLinear(float linear) = 0;
	virtual float GetQuadratic() = 0;
	virtual void SetQuadratic(float quadratic) = 0;
};

#endif //!__CAPS_INTERFACE_POINT_LIGHT__