#include "Skybox.hpp"


void Skybox::OnPlayAwake()
{

}

void Skybox::OnPlayStart()
{
	skyboxBuffer = ge::ModelManager->AllocateBuffer("../Model/skybox.obj");
	skyboxModel = ge::ModelManager->CreateModel(skyboxBuffer);
	skyboxAlbedoTexture = ge::TextureManager->CreateTexture("../TextureTest/skybox.png");
	skyboxMaterial = ge::MaterialManager->AllocateMaterial();
	skyboxMaterial->SetAlbedoTexture(skyboxAlbedoTexture);
	skyboxMaterial->SetLightActive(false);
	skyboxModel->SetMaterial(skyboxMaterial);
	skyboxModel->setScale(Vector3(ge::Camera->getCurrentCamera()->getFar()*0.97f));
}

void Skybox::OnPreUpdate()
{

}

void Skybox::OnPostUpdate()
{
	Vector3 pos = ge::Camera->getCurrentCamera()->getPosition();
	Vector3 rot = ge::Camera->getCurrentCamera()->getEulerAngles();
	if (ge::Input->GetKey(KEY_P))
	{
		std::cout << "Position : " << pos.x << " " << pos.y << " " << pos.z << std::endl;
		std::cout << "Rotation : " << rot.x << " " << rot.y << " " << rot.z << std::endl;
	}
	skyboxModel->setPosition(pos);
}

void Skybox::OnTriggerEnter()
{
}

void Skybox::OnTriggerExit()
{
}

void Skybox::OnTriggerStay()
{
}

void Skybox::OnGUI()
{

}

void Skybox::OnPlayStop()
{

}
