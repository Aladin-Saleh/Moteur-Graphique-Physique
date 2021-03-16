#include "TestEntry.hpp"

void OnEntryRegistration()
{
	SceneManager::RegisterEntry(new TestEntry());
	ge::Debug->log("OnEntryRegistration Test");
}

void TestEntry::LoadEntryScene()
{
	SceneManager::LoadLevel("Scene1");
}

void TestEntry::ProjectSetting()
{
	ge::Setting->SetName("Dll Caps");
	ge::Setting->SetWindowHeight(800);
	ge::Setting->SetWindowWidth(1200);
	ge::Setting->SetGravity(Vector3(0,-9.81,0));
	ge::Setting->SetFps(60);
	version v;
	v.patch = 0;
	v.mineur = 0;
	v.majeur = 1;
	ge::Setting->SetVersion(v);
}
