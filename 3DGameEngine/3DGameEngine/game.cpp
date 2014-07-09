#include "game.h"
#include <iostream>
#include <vector>



Mesh* TestMesh;
Material* TestMaterial;
PointLight TestPointLight1(BaseLight(glm::vec3(0, 1, 0), .8), Attenuation(0, 0, .01), glm::vec3(3.0, 0.0, 0.0), 10.0);
PointLight TestPointLight2(BaseLight(glm::vec3(1, 0, 0), .8), Attenuation(0, 0, .01), glm::vec3(-3.0, 0.0, 0.0), 10.0);
std::vector<PointLight> TestPointLights;


Game::Game(PhongShader* shader, double screenWidth, double screenHeight) :
m_shader(shader)
{
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> textCoords;

	m_camera = new Camera();
	m_camera->reinitPerspectiveMatrix(.01f, 1000.0f, 70.0f, 800.0f, 600.0f);
	
	vertices.push_back(glm::vec3(-1.0, -1.0, -1.0));
	vertices.push_back(glm::vec3( 0.0,  1.0,  0.0));
	vertices.push_back(glm::vec3( 1.0, -1.0,  0.0));
	vertices.push_back(glm::vec3( 0.0, -1.0,  1.0));

	indices.push_back(3); indices.push_back(1); indices.push_back(0);
	indices.push_back(2); indices.push_back(1); indices.push_back(3);
	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(0); indices.push_back(2); indices.push_back(3);

	textCoords.push_back(glm::vec2(0.0, 0.0));
	textCoords.push_back(glm::vec2(0.5, 1.0));
	textCoords.push_back(glm::vec2(1.0, 0.0));
	textCoords.push_back(glm::vec2(0.5, 1.0));

	TestPointLights.push_back(TestPointLight1);
	TestPointLights.push_back(TestPointLight2);
	m_shader->setPointLights(&TestPointLights);


	//TestMesh = new Mesh("./res/object_files/box.obj");
	TestMesh = new Mesh(vertices, indices, textCoords);
	TestMaterial = new Material("./res/texture_files/bricks.jpg", glm::vec3(1.0, 1.0, 1.0), 1, 8);
	//TestMaterial = new Material(glm::vec3(0.0, 1.0, 1.0));
	m_worldTransform = new Transform();
}


Game::~Game()
{
}

void Game::ProcessInput(Input* &m_input)
{
	m_camera->input(*m_input);
}

void Game::Update()
{
	float tmpUpdate = std::sin(Time::GetTime());
	m_worldTransform->setTranslationExplicit(0.0, 0.0, 5.0f);
	//m_worldTransform->setRotationExplicit(0.0, tmpUpdate*360.0, 0.0);
	//m_worldTransform->setScaleExplicit(tmpUpdate, tmpUpdate, tmpUpdate);

	TestPointLights[0].m_position = glm::vec3(3.0 + tmpUpdate*4, 0.0, 0.0);
	TestPointLights[1].m_position = glm::vec3(-3.0 + -tmpUpdate*4, 0.0, 0.0);
}

void Game::Render()
{
	m_shader->Bind();
	m_shader->updateBasicUniformsAndTexture(*m_camera, m_worldTransform->getTransformation(), *TestMaterial);
	TestMesh->Draw();
}
