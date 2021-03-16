#include "Scene_Aladin.hpp"

void Scene_Aladin::Load()
{
	/*bufferPlate = ge::ModelManager->AllocateBuffer("../ModelTest/plate.OBJ");
	buffer3 = ge::ModelManager->AllocateBuffer("../ModelTest/crate.OBJ");
	testTexture = ge::TextureManager->CreateTexture("../TextureTest/tile4b_basecolor.png");
	poupeTexture = ge::TextureManager->CreateTexture("../TextureTest/vil_p_crate06_d.png");
	shape = ge::ModelManager->CreateModel(bufferPlate);
	shape3 = ge::ModelManager->CreateModel(buffer3);

	shape->SetPosition(Vector3(0.0, -1.0, -7.0));
	shape->SetScale(Vector3(2, 1.0, 2));
	shape3->SetPosition(Vector3(0.0, 0.0, -7.0));
	shape3->SetScale(Vector3(4.0, 4.0, 4.0));
	shape->SetTexture(testTexture);
	shape3->SetTexture(poupeTexture);

	std::vector<Model*> m_model;

	m_model.resize(10);
	for (int i = 0; i < 10; i++)
	{
		m_model[i] = ge::ModelManager->CreateModel(buffer3);
		m_model[i]->SetPosition(Vector3(0, i * 2, 0));
		m_model[i]->SetScale(Vector3(4.0, 4.0, 4.0));
		m_model[i]->SetTexture(poupeTexture);
	}

	PluginManager::RegisterPlugin(new PluginTest2(shape3, poupeTexture, craneTexture, m_model));

	ge::Sound->CreateSoundBuffer("../SoundTest/wind.wav", "MonAudio01");
	audio01 = ge::Sound->AllocateAudioSource();
	audio01->SetSoundBuffer("MonAudio01");
	audio01->Play();
	ge::Camera->getCurrentCamera()->setPosition(Vector3(0, -5, -5));*/
}

void Scene_Aladin::UnLoad()
{
	/*ge::ModelManager->DestroyBuffer(bufferPlate);
	ge::Sound->ReleaseAudioSource(audio01);
	ge::Sound->ReleaseSoundBuffer("MonAudio01");
	PluginManager::UnregisterAllPlugin(); */
}
