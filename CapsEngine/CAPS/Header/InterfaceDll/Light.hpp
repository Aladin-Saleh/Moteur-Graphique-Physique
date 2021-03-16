#ifndef __CAPS_INTERFACE_LIGHT__
#define __CAPS_INTERFACE_LIGHT__

#include "Vector3.hpp"
#include "GraphicsObject.hpp"

class Light: public virtual GraphicsObject
{
public:
	virtual void SetColors(Vector3 color) = 0;
	virtual Vector3 GetColors() = 0;
	virtual void SetSpecular(Vector3 spec) = 0;
	virtual Vector3 GetSpecular() = 0;
	virtual Vector3 GetDirection() = 0;
	virtual void SetDirection(Vector3 direction) = 0;
	virtual void SetAmbiant(Vector3 ambiant) = 0;
	virtual Vector3 GetAmbiant() = 0;
	virtual void SetShadow(bool state) = 0;
};

#endif // !__CAPS_INTERFACE_LIGHT__
