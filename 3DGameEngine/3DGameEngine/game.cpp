#include "game.h"
#include "mesh.h"
#include "vertex.h"
#include <iostream>


Mesh* TriangleMesh;

Game::Game()
{
	Vertex Triangle[] = {	Vertex(glm::vec3(0.0, 1.0, 0.0)),
							Vertex(glm::vec3(1.0, -1.0, 0.0)), 
							Vertex(glm::vec3(-1.0, -1.0, 0.0)) };

	TriangleMesh = new Mesh(Triangle, sizeof(Triangle)/sizeof(Triangle[0]));
}


Game::~Game()
{
}

void Game::ProcessInput(Input* &m_input)
{
	if (m_input->GetKeyDown(82))
		std::cout << "up key pressed" << std::endl;

	if (m_input->GetKeyUp(82))
		std::cout << "up key released" << std::endl;
}

void Game::Update()
{

}

void Game::Render()
{
	TriangleMesh->Draw();
}
