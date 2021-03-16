#include "AAA.hpp"

void AAA::Load()
{
	buffer = ge::ModelManager->AllocateBuffer("../ModelTest/plate.obj");
	buffer3 = ge::ModelManager->AllocateBuffer("../ModelTest/crate.obj");
	testTexture = ge::TextureManager->CreateTexture("../TextureTest/tile4b_basecolor.png");

	poupeTexture = ge::TextureManager->CreateTexture("../TextureTest/vil_p_crate06_d.png");
	shape = ge::ModelManager->CreateModel(buffer);
	shape->SetTag("test");
	shape3 = ge::ModelManager->CreateModel(buffer3);

	shape->setPosition(Vector3(0.0, -1.0, -7.0));
	shape->setScale(Vector3(2, 1.0, 2));
	shape3->setPosition(Vector3(0.0, 0.0, -7.0));
	shape3->setScale(Vector3(4.0, 4.0, 4.0));
	Material * materialTest = ge::MaterialManager->AllocateMaterial();
	Material * materialpoupe = ge::MaterialManager->AllocateMaterial();
	materialTest->SetAlbedoTexture(testTexture);
	materialpoupe->SetAlbedoTexture(poupeTexture);
	shape->SetMaterial(materialTest);
	//shape->SetMaterial(industrial_Material);
	shape3->SetMaterial(materialpoupe);

	std::vector<Model *> m_model;

	m_model.resize(10);
	for (int i = 0; i < 10; i++)
	{
		m_model[i] = ge::ModelManager->CreateModel(buffer3);
		m_model[i]->setPosition(Vector3(0,i*2,0));
		m_model[i]->setScale(Vector3(4.0, 4.0, 4.0));
		m_model[i]->SetMaterial(materialpoupe);
	}

	PluginManager::RegisterPlugin(new PluginTest2(shape3, poupeTexture,craneTexture, m_model));

	/*ge::Sound->CreateSoundBuffer("../SoundTest/wind.wav", "MonAudio01");
	audio01 = ge::Sound->AllocateAudioSource();
	audio01->SetSoundBuffer("MonAudio01");
	audio01->Play();*/
	ge::Camera->getCurrentCamera()->setPosition(Vector3(0,5,5));

	
}

void AAA::UnLoad()
{
	ge::ModelManager->DestroyBuffer(buffer);
	//ge::Sound->ReleaseAudioSource(audio01);
	//ge::Sound->ReleaseSoundBuffer("MonAudio01");
	PluginManager::UnregisterAllPlugin();
}
