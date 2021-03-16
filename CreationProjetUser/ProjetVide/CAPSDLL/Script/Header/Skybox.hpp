#ifndef __CAPS_SKYBOX_PLUGIN__
#define __CAPS_SKYBOX_PLUGIN__

#include "PluginManager.hpp"
#include "SceneManager.hpp"
#include "Plugin.hpp"

class Skybox : public Plugin
{
public:
	 void OnPlayAwake() final;
	 void OnPlayStart() final;
	 void OnPreUpdate() final;
	 void OnPostUpdate() final;
	 void OnTriggerEnter() final;
	 void OnTriggerExit() final;
	 void OnTriggerStay() final;
	 void OnGUI() final;
	 void OnPlayStop() final;
private:
	Model * skyboxModel;
	ShapeBuffer * skyboxBuffer;
	Material * skyboxMaterial;
	Texture * skyboxAlbedoTexture;
	Vector3 posCam;
};

#endif //!__CAPS_SKYBOX_PLUGIN__