#ifndef __CAPS_INTERFACE_MODEL__
#define __CAPS_INTERFACE_MODEL__

#include "Material.hpp"
#include <iostream>
#include "GraphicsObject.hpp"

class Model : public virtual GraphicsObject
{
public:
	virtual void SetMaterial(Material * material) = 0;
	virtual Material * GetMaterial() = 0;
	virtual void SetTag(std::string tag = "UnTagged") = 0;
	virtual std::string GetTag() = 0;
};

#endif //!__CAPS_INTERFACE_MODEL__