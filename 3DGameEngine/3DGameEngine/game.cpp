#include "game.h"
#include "mesh.h"
#include "vertex.h"
#include "timing.h"
#include <iostream>



Mesh* TriangleMesh;

Game::Game(Shader* shader) :
m_shader(shader)
{
	
	shader->addUniform("transform");

	Vertex Triangle[] = {	Vertex(glm::vec3(-1.0f, -1.0f, 0.0f)),
							Vertex(glm::vec3( 0.0f,  1.0f, 0.0f)),
							Vertex(glm::vec3( 1.0f, -1.0f, 0.0f)) };

	TriangleMesh = new Mesh(Triangle, sizeof(Triangle)/sizeof(Triangle[0]));

	m_transform = new Transform(glm::vec3(0.0), glm::vec3(0.0));
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
	m_transform->setTranslationExplicit(std::sin(Time::GetTime()), 0.0, 0.0);
}

void Game::Render()
{
	m_shader->Bind();
	m_shader->setUniform("transform", m_transform->getTransformation());
	TriangleMesh->Draw();
}
