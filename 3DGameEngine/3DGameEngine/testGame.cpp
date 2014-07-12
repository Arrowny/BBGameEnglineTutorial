#include "testGame.h"
#include <iostream>
#include <vector>


GameObject root;
MeshRenderer* meshComponent;



TestGame::~TestGame()
{
}

void TestGame::Init(Window* window)
{

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> textCoords;

	m_camera = new Camera();
	m_camera->reinitPerspectiveMatrix(.01f, 1000.0f, 70.0f, window->GetWidth(), window->GetHeight());

	vertices.push_back(glm::vec3(-1.0, -1.0, -1.0));
	vertices.push_back(glm::vec3(0.0, 1.0, 0.0));
	vertices.push_back(glm::vec3(1.0, -1.0, 0.0));
	vertices.push_back(glm::vec3(0.0, -1.0, 1.0));

	indices.push_back(3); indices.push_back(1); indices.push_back(0);
	indices.push_back(2); indices.push_back(1); indices.push_back(3);
	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(0); indices.push_back(2); indices.push_back(3);

	textCoords.push_back(glm::vec2(0.0, 0.0));
	textCoords.push_back(glm::vec2(0.5, 1.0));
	textCoords.push_back(glm::vec2(1.0, 0.0));
	textCoords.push_back(glm::vec2(0.5, 1.0));

	



	//set up lighting
	PointLight TestPointLight1(BaseLight(glm::vec3(0, 1, 0), .8), Attenuation(0, 0, .01), glm::vec3(3.0, 0.0, 0.0), 10.0);
	PointLight TestPointLight2(BaseLight(glm::vec3(1, 0, 0), .8), Attenuation(0, 0, .01), glm::vec3(-3.0, 0.0, 0.0), 10.0);
	std::vector<PointLight> TestPointLights;
	SpotLight TestSpotLight1(PointLight(BaseLight(glm::vec3(0, 1, 0), .8), Attenuation(0, 0, .1), glm::vec3(0.0, 0.0, 0.0), 10.0), glm::vec3(0, 0, 1), 0.7);
	SpotLight TestSpotLight2(PointLight(BaseLight(glm::vec3(1, 0, 0), .8), Attenuation(0, 0, .1), glm::vec3(-3.0, 0.0, 0.0), 10.0), glm::vec3(0, 0, 1), 0.7);
	std::vector<SpotLight> TestSpotLights;
	m_shader = new PhongShader("./res/shaders/phongShader", glm::vec3(0.2, 0.2, 0.2));
	m_shader->m_dLight = DirectionalLight(BaseLight(glm::vec3(1, 1, 1), .8), glm::vec3(0, 1, 0));

	//m_shader->m_pointLights.push_back(TestPointLight1);
	//m_shader->m_pointLights.push_back(TestPointLight2);

	m_shader->m_spotLights.push_back(TestSpotLight1);
	m_shader->m_spotLights.push_back(TestSpotLight2);

	m_worldTransform = new Transform();

	//Set up mesh information.
	//TestMesh = new Mesh("./res/object_files/box.obj");
	meshComponent = new MeshRenderer(new Mesh(vertices, indices, textCoords),
		Material("./res/texture_files/bricks.jpg",
		glm::vec3(1.0, 1.0, 1.0), 1, 8), m_shader);
	root.m_camera = m_camera;
	root.m_transform = m_worldTransform;
	root.m_components.push_back(meshComponent);
}

void TestGame::ProcessInput(Input* &input)
{
	m_camera->input(*input);
}

void TestGame::Update()
{
	float tmpUpdate = std::sin(Time::GetTime());
	m_worldTransform->setTranslationExplicit(0.0, 0.0, 5.0);
	//m_worldTransform->setRotationExplicit(0.0, tmpUpdate*360.0, 0.0);
	//m_worldTransform->setScaleExplicit(tmpUpdate, tmpUpdate, tmpUpdate);

	//m_shader->m_pointLights[0].m_position = glm::vec3(3.0 + tmpUpdate * 4, 0.0, 0.0);
	//m_shader->m_pointLights[1].m_position = glm::vec3(-3.0 + -tmpUpdate * 4, 0.0, 0.0);

	m_shader->m_spotLights[0].m_pLight.m_position = m_camera->m_pos;
	m_shader->m_spotLights[0].m_direction = m_camera->getCenter();

	m_shader->m_spotLights[1].m_pLight.m_position = glm::vec3(-3.0 + -tmpUpdate * 4, 0.0, 0.0);
}

void TestGame::Render()
{
	root.Render();
}
