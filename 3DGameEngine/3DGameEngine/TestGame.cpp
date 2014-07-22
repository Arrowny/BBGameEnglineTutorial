#include "TestGame.h"

TestGame::TestGame()
{

}

TestGame::~TestGame()
{
	if (m_mesh) delete m_mesh;
	if (m_meshRenderer) delete m_meshRenderer;
}

void TestGame::init()
{
	m_mesh = new Mesh("./res/plane.obj");
//	m_material = Material(new Texture("./res/pikaqiu2.jpg"), glm::fvec3(1.0, 1.0, 1.0), 2, 32);

	m_material.AddTexture("pikaqiu", new Texture("./res/pikaqiu2.jpg"));
	m_material.AddFloat("specularIntensity", 1);
	m_material.AddFloat("specularPower", 8);

	m_meshRenderer = new MeshRenderer(*m_mesh, m_material);

	GameObject* planeObject = new GameObject();
	planeObject->AddComponent(m_meshRenderer);
	planeObject->GetTransform().SetPos(glm::vec3(0, -1, 7));

	//GameObject* testMesh1 = new GameObject();
	//testMesh1->AddComponent(new MeshRenderer(*m_mesh, m_material));
	////testMesh1->AddComponent(new Camera(70.0f, (float)WindowParameter::width / (float)WindowParameter::height, 1.0, 1000.0));
	//testMesh1->GetTransform().SetPos(glm::vec3(0, -1, 0));
	//planeObject->AddChild(testMesh1);
	

	GameObject* directionalLightObject = new GameObject();
	DirectionalLight* directionalLight = new DirectionalLight(glm::vec3(1, 1, 0), 0.1f/*, glm::vec3(0, 1, 1)*/);
	directionalLightObject->GetTransform().SetRot(glm::normalize(glm::quat(glm::radians(90.0f), 1.0, 0.0, 0.0)));
	directionalLightObject->AddComponent(directionalLight);

	GameObject* pointLightObject = new GameObject();
	PointLight* pointLight = new PointLight(glm::vec3(0, 1, 0), 0.2f, Attenuation(0.0, 0.0, 0.5));
	pointLightObject->AddComponent(pointLight);

	GameObject* spotLightObject = new GameObject();
	SpotLight* spotLight = new SpotLight(glm::fvec3(0.0, 0.0, 1.0), 0.6f, Attenuation(0.0, 0.0, 0.1), 0.1f);
	spotLightObject->AddComponent(spotLight);

	//std::cout << spotLight->GetTransform().GetPos().x << "," << spotLight->GetTransform().GetPos().y << "," << spotLight->GetTransform().GetPos().z << std::endl;
	spotLight->GetTransform().SetPos(glm::vec3(0, 0, 5));
	spotLight->GetTransform().SetRot(glm::normalize(glm::quat(glm::radians(-90.0f), 0.0, 1.0, 0.0)));

	AddObject(planeObject);
	AddObject(directionalLightObject);
	AddObject(pointLightObject);
	AddObject(spotLightObject);

	GameObject* cameraObject = new GameObject();
	cameraObject->AddComponent(new Camera(70.0f, (float)WindowParameter::width / (float)WindowParameter::height, 1.0, 1000.0));
	AddObject(cameraObject);

	GameObject* testMesh1 = new GameObject();
	GameObject* testMesh2 = new GameObject();
	testMesh1->AddComponent(new MeshRenderer(*m_mesh, m_material));
	testMesh2->AddComponent(new MeshRenderer(*m_mesh, m_material));

	testMesh1->GetTransform().SetPos(glm::vec3(0, 1, 0));
	testMesh1->GetTransform().SetRot(glm::quat(glm::radians(-90.0f), glm::vec3(0, 1, 0)));
	testMesh1->GetTransform().SetScale(glm::vec3(0.2f, 0.2f, 0.2f));

	testMesh2->GetTransform().SetPos(glm::vec3(0, 1, 5));

	testMesh1->AddChild(testMesh2);

	/*GameObject* cameraObject2 = new GameObject(); 
	cameraObject2->AddComponent(new Camera(70.0f, (float)WindowParameter::width / (float)WindowParameter::height, 1.0, 1000.0));


	testMesh2->AddChild(cameraObject2);*/
	AddObject(testMesh1);

	/* -------------------------------Light Part----------------------------------------
	m_shader->SetAmbient(glm::fvec3(0.3, 0.3, 0.3));
	m_shader->SetDirectionalLight(DirectionalLight(BaseLight(glm::vec3(1, 0, 0), 0.5f), glm::vec3(0, 0, -1)));
	
	
	////PointLight* m_pl = new PointLight[]
	//	{
	//	PointLight(BaseLight(glm::fvec3(1.0, 0.8, 0.0), 1.0f), Attenuation(0.0, 0.0, 1.0), glm::fvec3(2.0, 0.0, 3.0)),
	//		PointLight(BaseLight(glm::fvec3(0.0, 0.0, 1.0), 1.0f), Attenuation(0.0, 0.0, 1.0), glm::fvec3(-2.0, 0.0, 3.0))
	//	};
	//m_pl[0] = pl[0];
	//m_pl[1] = pl[1];
	
	PointLight* m_pl = &pl[0];
	m_shader->SetPointLights(m_pl, 2);
	
	SpotLight* m_sl = &sl[0];
	m_shader->SetSpotLights(m_sl, 1);*/
}

/*
void TestGame::input(Input& input){
	m_camera.Input(input);
	m_root.input();
}

float temp = 0.0f;

void TestGame::update(){
	//temp += Time::getDelta();

	m_root.GetTransform().SetPos(glm::vec3(0, -1, 7));
	m_root.update();

	/*-----------------------------------Light----------------------------------------------
	m_transform->SetPos(glm::vec3(sin(temp), 0, cos(temp)));
	m_transform->SetRot(glm::vec3(temp * 100, temp * 100, temp * 100));
	
	pl[0].SetPosition(glm::fvec3(0.0, 0.0, 8.0* (float)(sin(temp) + 1.0 / 2.0) + 10));
	pl[1].SetPosition(glm::fvec3(2.0, 0.0, 8.0* (float)(cos(temp) + 1.0 / 2.0) + 10));
	
	PointLight* m_pl = &pl[0];
	m_shader->SetPointLights(m_pl, 2);
	
	
	sl[0].GetPointLight()->SetPosition(m_camera->GetPos());
	sl[0].SetDirection(m_camera->GetForward()); 

	------------------------------------------------------------------------------------------
}

void TestGame::render(){
	m_root.render(&m_camera);
}
*/