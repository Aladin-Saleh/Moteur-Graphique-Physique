#include "PluginTest2.hpp"

PluginTest2::PluginTest2(Model * shape, Texture * texture, Texture * texture2, std::vector<Model *> mol)
{
	//const char * test = ge::Input->GetGamepadName(0);
	//ge::Debug->log("%s", test);
	shapeP = shape;
	textureP = texture;
	textureC = texture2;
	m_model = mol;
	waitTime = 0.0f;
	skyboxBuffer = ge::ModelManager->AllocateBuffer("../ModelTest/skybox.obj");
	SphereBuffer = ge::ModelManager->AllocateBuffer("../ModelTest/sphere.obj");
	//autreBuffer = ge::ModelManager->AllocateBuffer("../ModelTest/craneo.OBJ");
	skyboxShape = ge::ModelManager->CreateModel(skyboxBuffer,"Skybox");
	shapeSphere = ge::ModelManager->CreateModel(SphereBuffer);
	//autreModel = ge::ModelManager->CreateModel(autreBuffer);
	
	cam = ge::Camera->getCurrentCamera();
	shapeSphere->setPosition(Vector3(0,7,-7));

	Texture * autreTexture = ge::TextureManager->CreateTexture("../TextureTest/difuso_flip_oscuro.jpg");
	Texture * textureSphere = ge::TextureManager->CreateTexture("../TextureTest/Stand_albedo.jpeg");
	Texture * skybox = ge::TextureManager->CreateTexture("../TextureTest/skybox1.png");
	Texture * sphereMetal = ge::TextureManager->CreateTexture("../TextureTest/worn-shiny-metal-Metallic.png");
	Material * matautreTexture = ge::MaterialManager->AllocateMaterial();
	Material * mattextureSphere = ge::MaterialManager->AllocateMaterial();
	Material * matskybox = ge::MaterialManager->AllocateMaterial();
	matskybox->SetLightActive(false);
	matautreTexture->SetAlbedoTexture(autreTexture);
	mattextureSphere->SetAlbedoTexture(textureSphere);
	mattextureSphere->SetMetallicTexture(sphereMetal);
	mattextureSphere->SetMetallic(64.0f);
	mattextureSphere->SetOffset(Vector2(1.0f));
	matskybox->SetAlbedoTexture(skybox);
	//autreModel->SetMaterial(matautreTexture);
	skyboxShape->SetMaterial(matskybox);
	shapeSphere->SetMaterial(mattextureSphere);

	Vector3 boxSize = Vector3(1.1f);
	CollisionBoxShape * bs = ge::PhysicsEngine->CreateBoxCollisionShape(boxSize,10);
	CollisionBoxShape * bs2 = ge::PhysicsEngine->CreateBoxCollisionShape(Vector3(10, 1, 10), 0);	
	CollisionSphereShape * bs3 = ge::PhysicsEngine->CreateSphereCollisionShape(1.0f, 5);
	//CollisionVertexShape * bs4 = ge::PhysicsEngine->CreateVertexCollisionShape(autreBuffer,0);
	
	//rbAutre = ge::PhysicsEngine->AllocateRigidbody(bs4->GetCollisionShape());
	//rbAutre->forceActivationState(BT_DISABLE_DEACTIVATION);

	rbSphere = ge::PhysicsEngine->AllocateRigidbody(bs3->GetCollisionShape());
	rb = ge::PhysicsEngine->AllocateRigidbody(bs->GetCollisionShape());
	rb2 = ge::PhysicsEngine->AllocateRigidbody(bs2->GetCollisionShape());
	rbSphere->forceActivationState(BT_DISABLE_DEACTIVATION);
	rb->forceActivationState(BT_DISABLE_DEACTIVATION);

	rb->Translate(Vector3(0,10,-7));
	rb2->Translate(Vector3(0, -1.5, -7));
	rbSphere->Translate(Vector3(0, 5, -7));
	//rbAutre->Translate(Vector3(3, 7, -7));
	ge::PhysicsEngine->AddRigidbody(rb);//collision
	ge::PhysicsEngine->AddRigidbody(rb2);
	ge::PhysicsEngine->AddRigidbody(rbSphere);
	//ge::PhysicsEngine->AddRigidbody(rbAutre);
	m_rigidbody.resize(m_model.size());
	for (int i = 0; i < m_rigidbody.size(); i++)
	{
		m_rigidbody[i] = ge::PhysicsEngine->AllocateRigidbody(ge::PhysicsEngine->CreateBoxCollisionShape(Vector3(1.1f, 1.1f, 1.1f), 10)->GetCollisionShape());
		m_rigidbody[i]->setPosition(Vector3(boxSize.x, boxSize.y + i * 2, boxSize.z));
		m_rigidbody[i]->SetActiveCollision(true);
		ge::PhysicsEngine->AddRigidbody(m_rigidbody[i]);
	}
	/*Texture * tv_albedo = ge::TextureManager->CreateTexture("../TextureTest/TV_albedo.jpg");
	Texture * tv_metallic = ge::TextureManager->CreateTexture("../TextureTest/TV_metallic.jpg");
	Texture * tv_normal = ge::TextureManager->CreateTexture("../TextureTest/TV_normal.jpg");
	Texture * tv_rougness = ge::TextureManager->CreateTexture("../TextureTest/TV_roughness.jpg");
	Texture * tv_oclusion = ge::TextureManager->CreateTexture("../TextureTest/TV_AO.jpg");
	tv_Material = ge::MaterialManager->AllocateMaterial();
	tv_Material->SetAlbedoTexture(tv_albedo);
	tv_Material->SetMetallicTexture(tv_metallic);
	tv_Material->SetNormalTexture(tv_normal);
	tv_Material->SetOclusionTexture(tv_oclusion);
	tv_Material->SetRoughnessTexture(tv_rougness);
	ShapeBuffer * tv_Buffer = ge::ModelManager->AllocateBuffer("../ModelTest/tv.obj");
	tv_model = ge::ModelManager->CreateModel(tv_Buffer);
	tv_model->SetMaterial(tv_Material);
	tv_model->setPosition(Vector3(-20,20,-20));	
	tv_model->SetScale(Vector3(5,5,5));
	tv_Material->SetMetallic(32.0f);
	tv_Material->SetColor(Vector3(1.0f,1.0f,1.0f));

	Model * tv_model1 = ge::ModelManager->CreateModel(tv_Buffer);
	Model * tv_model2 = ge::ModelManager->CreateModel(tv_Buffer);
	Model * tv_model3 = ge::ModelManager->CreateModel(tv_Buffer);
	Model * tv_model4 = ge::ModelManager->CreateModel(tv_Buffer);
	Model * tv_model5 = ge::ModelManager->CreateModel(tv_Buffer);
	tv_model1->SetMaterial(tv_Material);
	tv_model2->SetMaterial(tv_Material);
	tv_model3->SetMaterial(tv_Material);
	tv_model4->SetMaterial(tv_Material);
	tv_model5->SetMaterial(tv_Material);
	tv_model1->setPosition(Vector3(-20, 25, -15));
	tv_model2->setPosition(Vector3(-20, 25, -10));
	tv_model3->setPosition(Vector3(-20, 25, -5));
	tv_model4->setPosition(Vector3(-20, 25, 0));
	tv_model5->setPosition(Vector3(-20, 25, 5));*/

	testlight = ge::LightManager->CreatePointLight(Vector3(0, 5, -7),Vector3(1.0f,0,0)*5);
	De = ge::LightManager->CreateDirectionalLight(Vector3(-60, -45, 135), Vector3(1,1,0.8f)*2);
	De->SetSpecular(Vector3(1.0f));
	De->SetAmbiant(Vector3(0.1f));
	De->setPosition(Vector3(0.0f, 15.0f, -15.0f));
	De->SetShadow(false);
	PointLight * testlight2 = ge::LightManager->CreatePointLight(Vector3(5, 5, -6), Vector3(0.0f, 1.0f, 0.0f) * 3);
}

void PluginTest2::OnPlayAwake()
{
	ge::Debug->log("OnPlayAwake PluginTest2"); 
}

void PluginTest2::OnPlayStart()
{
	m_fpsTest = ge::Setting->GetFps();
}

void PluginTest2::OnPreUpdate()
{
	if (ge::Input->GetKeyDown(KEY_DOWN))
	{
		ge::Setting->SetFps(m_fpsTest--);
		ge::Debug->log("FPS : %f",m_fpsTest);
	}
	if (ge::Input->GetKeyDown(KEY_UP))
	{
		ge::Setting->SetFps(m_fpsTest++);
		ge::Debug->log("FPS : %f", m_fpsTest);
	}

	if (ge::Input->GetKey(KEY_LEFT))
	{
		ge::Setting->SetFps(m_fpsTest--);
		ge::Debug->log("FPS : %f", m_fpsTest);
	}
	if (ge::Input->GetKey(KEY_RIGHT))
	{
		ge::Setting->SetFps(m_fpsTest++);
		ge::Debug->log("FPS : %f", m_fpsTest);
	}
	if (ge::Input->GetKeyDown(KEY_H))
	{
		stateHud = !stateHud;
		ge::ui->setActiveUI(stateHud);
	}
}

void PluginTest2::OnPostUpdate()
{
	/*for (int i = 0; i < 16; i++) 
	{
		if (ge::Input->GetGamepadState(0,i)) 
		{
			//ge::Debug->log("key %d", i);
		}
	}
	float axis;
	for (int i = 0; i < 6; i++)
	{
		axis = ge::Input->GetGamepadAxis(0, i);
		ge::Debug->log("key %f", axis);
	}*/
	/*waitTime += ge::Time->getDeltaTime();
	if (waitTime > 0.5f)
	{
		if (state)
		{
			shapeP->SetTexture(textureP);			
		}
		else
		{
			shapeP->SetTexture(textureC);
		}
		state = !state;
	
		waitTime = 0.0f;
	}; */
	for (int i = 0; i < m_rigidbody.size(); i++)
	{
		m_model[i]->setPosition(m_rigidbody[i]->getPosition());
		m_model[i]->setRotation(m_rigidbody[i]->getRotation());
	}

	//autreModel->SetPosition(rbAutre->GetPosition());
	//autreModel->SetRotation(rbAutre->GetRotation());

	shapeSphere->setPosition(rbSphere->getPosition());
	shapeSphere->setRotation(rbSphere->getRotation());

	if (ge::Input->GetKeyDown(KEY_J))
	{
		rb->setPosition(Vector3(0,10,-7));
	}
	if (ge::Input->GetKeyDown(KEY_K))
	{
		rb->ApplyImpulse(Vector3(0,10,0), rb->getPosition());
	}
	if (ge::Input->GetKey(KEY_I))
	{
		rb->setEulerAngles(Vector3(0,ge::Time->getTime()*90,0));
	}
	if (ge::Input->GetKey(KEY_O) || ge::Input->GetGamepadState(0,JOYSTICK_1))
	{
		rbSphere->setPosition(Vector3(+ge::Input->GetGamepadAxis(0, 0) * 5, 2, -7+ ge::Input->GetGamepadAxis(0, 1)*5));
	}
	if (ge::Input->GetKeyDown(KEY_P))
	{
		rbSphere->ApplyImpulse(Vector3(0, 2, -7), rb->getPosition());
	}

	/*for (int i = 0; i < 348; i++) {
		if (ge::Input->GetKey(i)) {
			ge::Debug->log("key %d", i);
		}
	}*/

	/*if (ge::Input->GetKey(KEY_T))
	{		
		tv_Material->SetMetallic(tv_Material->GetMetallic() + ge::Time->getDeltaTime());
		ge::Debug->log("%f", tv_Material->GetMetallic());
	}
	if (ge::Input->GetKey(KEY_G))
	{
		tv_Material->SetMetallic(tv_Material->GetMetallic() - ge::Time->getDeltaTime());
		ge::Debug->log("%f", tv_Material->GetMetallic());
	}
	if (!ge::Input->GetKey(KEY_B))
	{
		tv_model->SetEulerAngles(Vector3(0, fmod(ge::Time->getTime() * 60, 360), 0));
	}*/

	
	shapeP->setPosition(rb->getPosition());
	shapeP->setRotation(rb->getRotation());

	skyboxShape->setPosition(cam->getPosition());
	skyboxShape->setScale(Vector3(cam->getFar()*0.97f));
	//De->SetPosition(Vector3(std::sin(ge::Time->getTime())*20, 15.0f, -15.0f));
	//testlight->SetPosition(Vector3(-test.x, -test.y, -test.z));
	/*Hit hit;
	if (ge::RayCast->Ray(Vector3(-test.x, -test.y, -test.z), Vector3(0, -1, 0), &hit,20.0f, "test"))
	{
		ge::Debug->log("hit distance : %f", hit.distance);
		rbSphere->SetPosition(hit.position);
	}
	else
	{
		ge::Debug->warn("dont hit");
	}*/
}

void PluginTest2::OnTriggerEnter()
{
}

void PluginTest2::OnTriggerExit()
{
}

void PluginTest2::OnTriggerStay()
{
}

void PluginTest2::OnGUI()
{
}

void PluginTest2::OnPlayStop()
{
}
