#ifndef __CAPS_PLUGIN__
#define __CAPS_PLUGIN__

#include "EngineFonction.hpp"

class Plugin
{
public:
	virtual void OnPlayAwake() = 0;
	virtual void OnPlayStart() = 0;
	virtual void OnPreUpdate() = 0;
	virtual void OnPostUpdate() = 0;
	virtual void OnGUI() = 0;
	virtual void OnTriggerEnter() = 0;
	virtual void OnTriggerExit() = 0;
	virtual void OnTriggerStay() = 0;
	virtual void OnPlayStop() = 0;
};


#endif //__CAPS_PLUGIN__