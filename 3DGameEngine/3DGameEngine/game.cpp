#include "game.h"
#include <iostream>
#include <vector>



Mesh* TestMesh;
Texture* TestTexture;
Camera* camera;

Game::Game(Shader* shader, double screenWidth, double screenHeight) :
m_shader(shader)
{
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> textCoords;

	camera = new Camera();
	camera->reinitPerspectiveMatrix(.01f, 1000.0f, 70.0f, 800.0f, 600.0f);
	shader->addUniform("transform");
	
	vertices.push_back(glm::vec3(-0.5, -0.5, 0.0));
	vertices.push_back(glm::vec3( 0.0,  0.5, 0.0));
	vertices.push_back(glm::vec3( 0.5, -0.5, 0.0));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	textCoords.push_back(glm::vec2(0.0, 0.0));
	textCoords.push_back(glm::vec2(0.5, 1.0));
	textCoords.push_back(glm::vec2(1.0, 0.0));

	//TestMesh = new Mesh("./res/object_files/box.obj");
	TestMesh = new Mesh(vertices, indices, textCoords);
	TestTexture = new Texture("./res/texture_files/bricks.jpg");
	m_transform = new Transform();
}


Game::~Game()
{
}

void Game::ProcessInput(Input* &m_input)
{
	camera->input(*m_input);
}

void Game::Update()
{
	float tmpUpdate = std::sin(Time::GetTime());
	m_transform->setTranslationExplicit(tmpUpdate, 0.0, 5.0f);
	//m_transform->setRotationExplicit(0.0, tmpUpdate*360.0, 0.0);
	//m_transform->setScaleExplicit(tmpUpdate, tmpUpdate, tmpUpdate);
}

void Game::Render()
{
	m_shader->Bind();
	m_shader->setUniform("transform", camera->getPerspectiveTransform()*camera->getCameraTransform()*m_transform->getTransformation());
	TestTexture->Bind(0);
	TestMesh->Draw();
}
