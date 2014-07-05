#include "game.h"
#include <iostream>



Mesh* TestMesh;

Game::Game(Shader* shader, double screenWidth, double screenHeight) :
m_shader(shader)
{
	shader->addUniform("transform");
	TestMesh = new Mesh("./res/object_files/box.obj");
	m_transform = new Transform(glm::vec3(0.0), glm::vec3(0.0));
	m_transform->initProjectionMatrix(.01f, 1000.0f, 70.0f, 800.0f, 600.0f); 
}


Game::~Game()
{
}

void Game::ProcessInput(Input* &m_input)
{

	//DEBUG: Test code to make sure inputs are working correctly
	if (m_input->GetKeyDown(82))
		std::cout << "up key pressed" << std::endl;

	if (m_input->GetKeyUp(82))
		std::cout << "up key released" << std::endl;
}

void Game::Update()
{
	float tmpUpdate = std::sin(Time::GetTime());
	m_transform->setTranslationExplicit(tmpUpdate, 0.0, -5.0f);
	m_transform->setRotationExplicit(0.0, tmpUpdate*360.0, 0.0);
	//m_transform->setScaleExplicit(tmpUpdate, tmpUpdate, tmpUpdate);
}

void Game::Render()
{
	m_shader->Bind();
	m_shader->setUniform("transform", m_transform->getPerspectiveMatrix()*m_transform->getTransformation());
	TestMesh->Draw();
}
