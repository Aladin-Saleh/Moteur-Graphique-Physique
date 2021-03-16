#ifndef __CAPS_ENTRY__
#define __CAPS_ENTRY__

#include "EngineFonction.hpp"

class Entry
{
public:
	virtual void LoadEntryScene() = 0;
	virtual void ProjectSetting() = 0;
};

#ifndef __CAPS_GAME_ENGINE__
extern "C" void OnEntryRegistration();
#endif

#endif // __CAPS_ENTRY__
