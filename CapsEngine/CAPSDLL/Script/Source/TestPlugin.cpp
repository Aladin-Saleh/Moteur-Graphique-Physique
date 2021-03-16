#include "TestPlugin.hpp"


void TestPlugin::OnPlayAwake()
{
	ge::Debug->log("OnPlayAwake");
	ge::Debug->log("Fps: %lf", ge::Setting->GetFps());
}

void TestPlugin::OnPlayStart()
{
	ge::Debug->log("OnPlayStart");
	waitTime = 0.0f;
}

void TestPlugin::OnPreUpdate()
{
	waitTime += ge::Time->getFixedDeltaTime();
	if (waitTime > 0.0f)
	{
		SceneManager::LoadLevel("SceneAAA");
	}
}

void TestPlugin::OnPostUpdate()
{
}

void TestPlugin::OnTriggerEnter()
{
}

void TestPlugin::OnTriggerExit()
{
}

void TestPlugin::OnTriggerStay()
{
}

void TestPlugin::OnGUI()
{

}

void TestPlugin::OnPlayStop()
{
	ge::Debug->log("OnPlayStop");
}
