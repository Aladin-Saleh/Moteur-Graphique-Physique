#ifndef __CAPS_SCRIPT_S__
#define __CAPS_SCRIPT_S__

#include "PluginManager.hpp"
#include "SceneManager.hpp"
#include "Plugin.hpp"

class ScriptSchema : public Plugin
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
	
};

#endif