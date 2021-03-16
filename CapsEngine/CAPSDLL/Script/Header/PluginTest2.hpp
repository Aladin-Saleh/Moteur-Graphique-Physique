#ifndef __CAPS_PLUGIN_TEST_2__
#define __CAPS_PLUGIN_TEST_2__

#include "PluginManager.hpp"
#include "SceneManager.hpp"
#include "Plugin.hpp"

class PluginTest2 : public Plugin
{
public:
	PluginTest2(Model * shape, Texture * texture, Texture * texture2, std::vector<Model *> model);
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
	float m_fpsTest = 60.0f;
	float waitTime = 0.0f;
	bool state = false;
	Model * shapeP;
	Texture * textureP;
	Texture * textureC;
	ShapeBuffer * skyboxBuffer;
	Model * skyboxShape;
	I_Camera * cam;
	RigidBody * rb;
	RigidBody * rb2;
	ShapeBuffer * SphereBuffer;
	RigidBody * rbSphere;
	Model * shapeSphere;
	ShapeBuffer * autreBuffer;
	Model * autreModel;
	RigidBody * rbAutre;
	std::vector<Model *> m_model;
	std::vector<RigidBody  *> m_rigidbody;
	PointLight * testlight;
	DirectionalLight * De;
	Material * tv_Material;
	Model * tv_model;
	bool stateHud = true;
};

#endif // __CAPS_PLUGIN_TEST_2__