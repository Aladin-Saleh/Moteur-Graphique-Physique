#ifndef __CAPS_INTERFACE_RAY_CAST__
#define __CAPS_INTERFACE_RAY_CAST__

#include "Vector3.hpp"
#include "Model.hpp"
#include <iostream>

struct Hit
{
	Vector3 position;
	Vector3 normal;
	float distance;
	Model * model;
};

class I_RayCast
{
public:
	virtual bool Ray(Vector3 pos, Vector3 dir, Hit * hit, float maxDistance, std::string tag = "all") = 0;
};

#endif // !__CAPS_INTERFACE_RAY_CAST__
