#include "game.h"
#include <iostream>



Mesh* TestMesh;
Camera* camera;

Game::Game(Shader* shader, double screenWidth, double screenHeight) :
m_shader(shader)
{
	std::cout << "DELTA: " << Time::DELTA << std::endl;
	camera = new Camera();
	camera->reinitPerspectiveMatrix(.01f, 1000.0f, 70.0f, 800.0f, 600.0f);
	shader->addUniform("transform");
	TestMesh = new Mesh("./res/object_files/box.obj");
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
	TestMesh->Draw();
}
