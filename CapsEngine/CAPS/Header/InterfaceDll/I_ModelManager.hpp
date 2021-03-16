#ifndef __CAPS_INTERFACE_MODEL_MANAGER__
#define __CAPS_INTERFACE_MODEL_MANAGER__

#include "Model.hpp"
#include "ShapeBuffer.hpp"

class I_ModelManager
{
public:
	virtual ShapeBuffer * AllocateBuffer(const char * path) = 0;
	virtual Model * CreateModel(ShapeBuffer * buffer, std::string nom = "Model") = 0;
	virtual void DestroyModel(Model * model) = 0;
	virtual void DestroyBuffer(ShapeBuffer * buffer)  = 0;
};

#endif // !__CAPS_INTERFACE_MODEL_MANAGER__
