#ifndef __CAPS_INTERFACE_LIGHT_MANAGER__
#define __CAPS_INTERFACE_LIGHT_MANAGER__

#include "Light.hpp"
#include "SpotLight.hpp"
#include "PointLight.hpp"
#include "DirectionalLight.hpp"

class I_LightManager
{
public:
	virtual SpotLight * CreateSpotLight(Vector3 position, Vector3 color, Vector3 direction, float cutOff, float outerCutOff, std::string name = "SpotLight") = 0;
	virtual DirectionalLight * CreateDirectionalLight(Vector3 direction, Vector3 color, std::string name = "DirectionalLight") = 0;
	virtual PointLight * CreatePointLight(Vector3 position, Vector3 color, std::string name = "PointLight") = 0;
	virtual void DestroyLight(Light * light) = 0;
};

#endif // !__CAPS_INTERFACE_LIGHT_MANAGER__
