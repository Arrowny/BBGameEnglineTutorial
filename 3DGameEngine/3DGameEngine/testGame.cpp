#include "testGame.h"

TestGame::~TestGame()
{
	if (m_texture) delete m_texture;
	if (m_mesh) delete m_mesh;
	if (m_meshRenderer) delete m_meshRenderer;
}

void TestGame::init(){

	/*Vertex vertices[] = { Vertex(glm::vec3(-0.8, -0.8, 0.0), glm::vec2(1.0f, 0.0), glm::vec3(0, 0, -1)),
						  Vertex(glm::vec3(0.0, 0.8, 0.0), glm::vec2(0.5f, 0.0), glm::vec3(0, 0, -1)),
						  Vertex(glm::vec3(0.8, -0.8, 0.0), glm::vec2(1.0f, 0.0), glm::vec3(0, 0, -1)),
						  Vertex(glm::vec3(0.0, -0.8, 0.8), glm::vec2(0.0, 0.5f), glm::vec3(0, 0, -1)),
						  Vertex(glm::vec3(0.0, -0.8, -0.8), glm::vec2(0.0, 0.5f), glm::vec3(0, 0, -1)) };

	unsigned int indices[] = { 3, 1, 0,
	  						   2, 1, 3,
							   0, 2, 3,
							   4, 1, 2,
							   1, 4, 0,
							   2, 0, 4 };*/

	glm::fvec4 baseColor(1.0f, 1.0f, 1.0f, 1.0f);

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
	

	//m_mesh = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	m_mesh = new Mesh("triforce.obj");
	//m_mesh2 = new Mesh("./res/mon.obj");
	//m_mesh3 = new Mesh("./res/luigi.obj");
	m_texture = new Texture("colour.jpg");
	m_texture2 = new Texture("bricks2.jpg");
	m_texture3 = new Texture("bricks2_normal.jpg");
	m_texture4 = new Texture("particle.tga");
	//m_texture4 = new Texture("fireworks_red.tga");
	m_skyTexture = new Texture3d("skyleft.png", "skyright.png", "skyup.png", "skydown.png", "skyfront.png", "skyback.png");
    //m_skyTexture = new Texture3d("./res/skybox", "left2.jpg", "right2.jpg", "up2.jpg", "down2.jpg", "front2.jpg", "back2.jpg");

    //m_skyTexture = new Texture3d("./res/skybox", "jajlands1_left.jpg", "jajlands1_right.jpg", "jajlands1_top.jpg", "jajlands1_bottom.jpg", "jajlands1_front.jpg", "jajlands1_back.jpg");

	m_material = Material();
	m_material.AddTexture("diffuse", m_texture);
	m_material.AddFloat("specularIntensity", 1);
	m_material.AddFloat("specularPower", 36);

	m_material2 = Material();
	m_material2.AddTexture("diffuse", m_texture2);
	m_material2.AddFloat("specularIntensity", 1);
	m_material2.AddFloat("specularPower", 10);

	m_material3 = Material();
	m_material3.AddTexture("diffuse", m_texture3);
	m_material3.AddFloat("specularIntensity", 1);
	m_material3.AddFloat("specularPower", 36);

	m_material4 = Material();
	m_material4.AddTexture("diffuse", m_texture4);
	m_material4.AddFloat("specularIntensity", 1);
	m_material4.AddFloat("specularPower", 36);

	m_sky = Material();
	m_sky.AddTexture("diffuse", m_skyTexture);

	m_meshRenderer = new MeshRenderer(*m_mesh, m_material);
	m_meshRenderer2 = new MeshRenderer(*m_mesh, m_material2);
	m_meshRenderer3 = new MeshRenderer(*m_mesh, m_material3);

	m_skyBoxrenderer = new SkyBoxRenderer(m_sky);

	m_planeObject->AddComponent(m_meshRenderer);
	m_planeObject2->AddComponent(m_meshRenderer2);
	m_planeObject3->AddComponent(m_meshRenderer3);
	//m_planeObject2->AddComponent(new FreeLook());
	//m_planeObject2->AddComponent(new FreeMove());
	m_planeObject->AddChild(m_planeObject2);
	m_planeObject->AddChild(m_planeObject3);
	m_planeObject->GetTransform().SetPos(glm::fvec3(0, 0, 10));
	m_planeObject2->GetTransform().SetPos(glm::fvec3(-4, 0, 0));
	m_planeObject3->GetTransform().SetPos(glm::fvec3(-2, 4, 0));

	dirLight1 = new DirectionalLight(glm::fvec3(1.0f, 1.0f, 1.0f), 0.01f);
	dirLight2 = new DirectionalLight(glm::fvec3(0.0f, 0.0f, 1.0f), 0.2f);
	dirLight3 = new DirectionalLight(glm::fvec3(0.0f, 1.0f, 0.0f), 0.2f);
	m_dirLightObj1->AddComponent(dirLight1);
	//m_dirLightObj1->AddComponent(dirLight2);
	//m_dirLightObj1->AddComponent(dirLight3);
	m_dirLightObj1->GetTransform().SetRot(glm::normalize(glm::quat((float)-0.1f, 0.0f, 1.0f, 0.0f))); 

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

	m_basicPS = new ParticleSystem("basicParticlePhy", &m_material4, glm::vec3(1,1,5));
	m_basicPSObj->AddComponent(m_basicPS);
	m_basicPSObj->AddComponent(new FreeLook())->AddComponent(new FreeMove());

	AddToScene(m_planeObject);
	AddToScene(m_dirLightObj1);
	AddToScene(m_pLightObj1);
	AddToScene(m_sLightObj1);
	AddToScene(m_camera);
	AddToScene(m_skyBoxObject);
	AddToScene(m_basicPSObj);

	//m_planeObject->GetTransform().SetRot(glm::normalize(glm::quat(glm::radians(-90.0f), 0.0f, 1.0f, 0.0f)));
	//m_planeObject3->AddChild((new gameObject())->AddComponent(new Camera(70.0f, Window::getAspect(), 0.1f, 1000.0f))->AddComponent(new FreeLook()));
	//AddToScene((new gameObject())->AddComponent(new Camera(70.0f, Window::getAspect(), 0.1f, 1000.0f))->AddComponent(new FreeLook())->AddComponent(new FreeMove()));

}

void TestGame::update(float delta){

	float sinCounter = sinf(counter);
	float cosCounter = cosf(counter);

	//m_pLightObj1->GetTransform().SetPos(glm::vec3(sinCounter, 1.5, 4.5));
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
