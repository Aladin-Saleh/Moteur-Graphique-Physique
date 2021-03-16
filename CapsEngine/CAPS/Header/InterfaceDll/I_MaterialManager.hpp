#ifndef __CAPS_INTERFACE_MATERIAL_MANAGER__
#define __CAPS_INTERFACE_MATERIAL_MANAGER__

#include "Material.hpp"

class I_MaterialManager
{
public:
	virtual Material * AllocateMaterial() = 0;
	virtual void DestroyMaterial(Material * material) = 0;
};

#endif // !__CAPS_INTERFACE_MATERIAL_MANAGER__
