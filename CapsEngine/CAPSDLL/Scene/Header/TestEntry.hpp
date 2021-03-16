#ifndef __CAPS_TEST_ENTRY__
#define __CAPS_TEST_ENTRY__

#include "SceneManager.hpp"
#include "Entry.hpp"

class TestEntry : public Entry
{
public:
	void LoadEntryScene() final;
	void ProjectSetting() final;
};

#endif