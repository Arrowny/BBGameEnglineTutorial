#include "testGame.h"

TestGame::~TestGame()
{
	if (m_texture) delete m_texture;
	if (m_mesh) delete m_mesh;
	if (m_meshRenderer) delete m_meshRenderer;
}

void TestGame::init(){

	m_planeObject = new GameObject();
	m_planeObject2 = new GameObject();
	m_planeObject3 = new GameObject();
	m_dirLightObj1 = new GameObject();
	m_pLightObj1 = new GameObject();
	m_sLightObj1 = new GameObject();
	m_sLightObj2 = new GameObject();
	m_camera = new GameObject();
	m_skyBoxObject = new GameObject();
	m_basicPSObj = new GameObject();

	m_mesh = new Mesh("triforce.obj");
	//m_mesh2 = new Mesh("luigi.obj");
	//m_texture = new Texture("luigiD.jpg");
	m_texture = new Texture("colour.jpg");
	m_texture2 = new Texture("bricks2.jpg");
	m_texture3 = new Texture("bricks2_normal.jpg");
	m_skyTexture = new TextureCube("skyleft.png", "skyright.png", "skyup.png", "skydown.png", "skyfront.png", "skyback.png");
	m_particleTexture = new Texture("Particle.tga");

	m_material = Material(m_texture, 1, 36);
	m_material2 = Material(m_texture2, 1, 10);
	m_material3 = Material(m_texture3, 1, 36);
	m_particleMaterial = Material(m_particleTexture, 1, 36);
	m_particleMaterial2 = Material(m_particleTexture, 1, 36);
	m_particleMaterial3 = Material(m_particleTexture, 1, 36);
	m_sky = Material(); m_sky.SetTexture("diffuse", m_skyTexture);

	m_meshRenderer = new MeshRenderer(*m_mesh, m_material);
	m_meshRenderer2 = new MeshRenderer(*m_mesh, m_material2);
	m_meshRenderer3 = new MeshRenderer(*m_mesh, m_material3);

	m_skyBoxrenderer = new SkyBoxRenderer(m_sky);

	m_planeObject->AddComponent(m_meshRenderer);	
	m_planeObject2->AddComponent(m_meshRenderer2);
	m_planeObject3->AddComponent(m_meshRenderer3);
	m_planeObject->AddChild(m_planeObject2);
	m_planeObject->AddChild(m_planeObject3);
	m_planeObject->GetTransform().SetPos(glm::fvec3(0, 0, 10));
	m_planeObject2->GetTransform().SetPos(glm::fvec3(-4, 0, 0));
	m_planeObject3->GetTransform().SetPos(glm::fvec3(-2, 4, 0));

	dirLight1 = new DirectionalLight(glm::fvec3(1.0f, 1.0f, 1.0f), 1.0f);
	dirLight2 = new DirectionalLight(glm::fvec3(0.0f, 0.0f, 1.0f), 0.2f);
	dirLight3 = new DirectionalLight(glm::fvec3(0.0f, 1.0f, 0.0f), 0.2f);
	m_dirLightObj1->AddComponent(dirLight1);
	m_dirLightObj1->GetTransform().SetRot(glm::normalize(glm::quat(glm::radians(150.0f), 1.0f, 1.0f, 0.0f)));

	pLight1 = new PointLight(glm::fvec3(1.0f, 1.0f, 1.0f), 0.2f, Attenuation(0, 0, 1));
	pLight2 = new PointLight(glm::fvec3(0.0f, 1.0f, 0.0f), 0.2f, Attenuation(0, 0, 1));
	pLight3 = new PointLight(glm::fvec3(0.0f, 0.0f, 1.0f), 0.2f, Attenuation(0, 0, 1));
	m_pLightObj1->AddComponent(pLight1);
	//m_pLightObj1->AddComponent(pLight2);
	//m_pLightObj1->AddComponent(pLight3);
	//m_pLightObj1->GetTransform().SetPos(m_planeObject->GetTransform().GetTransformedPos());
	//m_pLightObj1->GetTransform().SetPos(glm::fvec3(0, 0, 0));

	sLight1 = new SpotLight(glm::fvec3(1, 0, 0), 0.4f, Attenuation(0, 0, 0.5f), 0.8f);
	sLight2 = new SpotLight(glm::fvec3(0, 1, 0), 0.4f, Attenuation(0, 0, 0.5f), 0.8f);
	m_sLightObj1->AddComponent(sLight1);
	m_sLightObj2->AddComponent(sLight2);
	m_sLightObj1->AddChild(m_sLightObj2);
	m_sLightObj2->GetTransform().SetPos(glm::fvec3(0.5, 0.0, 0.0));
	//m_sLightObj1->GetTransform().SetRot(glm::normalize(glm::quat(glm::radians(90.0f), 1.0, 0, 0)));
	m_sLightObj1->GetTransform().SetRot(glm::normalize(glm::quat(glm::radians(0.0f), 0.0, 0, 0)));
	//m_sLightObj2->GetTransform().SetPos(m_planeObject2->GetTransform().GetTransformedPos() + glm::fvec3(0.0, 1.2, -0.7));
	//m_sLightObj2->GetTransform().SetRot(glm::normalize(glm::quat(glm::radians(90.0f), 1.0, 0, 0)));

	m_camera->AddComponent(new Camera(70.0f, Window::getAspect(), 0.1f, 1000.0f))->AddComponent(new FreeLook())->AddComponent(new FreeMove());
	m_skyBoxObject->AddComponent(m_skyBoxrenderer);

	m_advectTexture = m_phyAdvect->CreateVelocityTexture(128, 256, 128);

	//m_basicPS = new ParticleSystem("basicParticlePhy", &m_material, new PhysicsComponents(2), glm::vec3(0.0, 0.0, 10.0), 100000);
	//m_material.SetFloat("quadLength", 0.1);
	m_luminousPS = new ParticleSystem("advectParticlePhy", &m_particleMaterial, new PhysicsComponents(2, m_advectTexture), glm::vec3(-2.0, 1.8, 10.0), 100000, LUMINOUS_BLEND);
	m_luminousPS2 = new ParticleSystem("basicParticlePhy", &m_particleMaterial, new PhysicsComponents(2), glm::vec3(-4.0, 0.0, 10.0), 1000, LUMINOUS_BLEND);
	m_luminousPS3 = new ParticleSystem("basicParticlePhy", &m_particleMaterial, new PhysicsComponents(2), glm::vec3(0.0, 0.0, 10.0), 1000, LUMINOUS_BLEND);
	m_particleMaterial.SetFloat("quadLength", 0.01);
	m_particleMaterial.SetVector3f("color", glm::fvec3(1.0, 1.0, 1.0));
	m_basicPSObj->AddComponent(m_luminousPS);
	m_basicPSObj->AddComponent(m_luminousPS2);
	m_basicPSObj->AddComponent(m_luminousPS3);
	
	AddToScene(m_planeObject);
	AddToScene(m_dirLightObj1);
	AddToScene(m_pLightObj1);
	AddToScene(m_sLightObj1);
	AddToScene(m_camera);
	AddToScene(m_skyBoxObject);
	AddToScene(m_basicPSObj);
}

void TestGame::update(float delta){

	float sinCounter = sinf(counter);
	float cosCounter = cosf(counter);

	m_pLightObj1->GetTransform().SetPos(m_planeObject->GetTransform().GetTransformedPos() + glm::fvec3(sinCounter, 1.5, -0.5));
	m_sLightObj1->GetTransform().SetPos(m_camera->GetTransform().GetTransformedPos());
	m_sLightObj1->GetTransform().SetRot(m_camera->GetTransform().GetTransformedRot());
	m_planeObject2->GetTransform().SetRot(glm::conjugate(m_camera->GetTransform().GetTransformedRot()));
	//m_sLightObj1->GetTransform().SetPos(m_planeObject->GetTransform().GetTransformedPos() + glm::vec3(sinCounter * 2 - 2, -1.2, -0.7));
	//m_sLightObj1->GetTransform().SetPos(m_planeObject->GetTransform().GetTransformedPos() + glm::vec3(sinCounter * 2 - 2, 0, -0.7));
	//m_planeObject->GetTransform().SetRot(glm::normalize(glm::quat(glm::radians(cosCounter*2), 0.0f, 1.0f, 0.0f)));
	m_root.updateAll(delta);

	counter += 0.0003f;
}
