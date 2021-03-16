#ifndef __CAPS_TEST_PLUGIN__
#define __CAPS_TEST_PLUGIN__

#include "PluginManager.hpp"
#include "SceneManager.hpp"
#include "Plugin.hpp"

class TestPlugin : public Plugin
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
	float waitTime = 0.0f;
};

#endif