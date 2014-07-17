#include "TestGame.h"


//PointLight pl[] = { PointLight(BaseLight(glm::fvec3(1.0, 0.5, 0.0), 0.8f), Attenuation(0.0, 0.0, 1.0), glm::fvec3(0.0, 0.0, 7.0), 4),
//PointLight(BaseLight(glm::fvec3(1.0, 0.0, 0.5), 0.8f), Attenuation(0.0, 0.0, 1.0), glm::fvec3(2.0, 0.0, 7.0), 4)
//};
//SpotLight sl[] = { SpotLight(PointLight(BaseLight(glm::fvec3(0.0, 1.0, 1.0), 1.0f), Attenuation(0.0, 0.0, 0.1), glm::fvec3(-2.0, 0.0, 0.0), 30), glm::fvec3(1.0, 1.0, 1.0), 0.1f)
//};

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
	/*m_camera = Camera();
	m_camera = Camera(glm::vec3(0, 1, -4), 70.0f, (float)WindowParameter::width / (float)WindowParameter::height, 1.0f, 1000.0f);*/

	m_mesh = new Mesh("./res/plane.obj");
	m_material = Material(new Texture("./res/pikaqiu2.jpg"), glm::fvec3(1.0, 1.0, 1.0), 2, 32);

	m_meshRenderer = new MeshRenderer(*m_mesh, m_material);

	GameObject* planeObject = new GameObject();
	planeObject->AddComponent(m_meshRenderer);
	planeObject->GetTransform().SetPos(glm::vec3(0, -1, 7));

	GetRootObject().AddChild(*planeObject);

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