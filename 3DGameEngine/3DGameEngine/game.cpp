#include "game.h"
#include <iostream>



Mesh* TestMesh;

Game::Game(Shader* shader) :
m_shader(shader)
{
	
	shader->addUniform("transform");

	//Vertex Triangle[] = {	Vertex(glm::vec3(-1.0f, -1.0f, 0.0f)),
	//						Vertex(glm::vec3( 0.0f,  1.0f, 0.0f)),
	//						Vertex(glm::vec3( 1.0f, -1.0f, 0.0f)) };
	//unsigned int Indices[] = { 0, 1, 2 };

	//TestMesh = new Mesh(Triangle, sizeof(Triangle) / sizeof(Triangle[0]), Indices, sizeof(Indices)/sizeof(Indices[0]));

	*TestMesh = Loader::LoadMesh("./res/object_files/box.obj");

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
	float tmpUpdate = std::sin(Time::GetTime());
	m_transform->setTranslationExplicit(tmpUpdate, 0.0, 0.0);
	m_transform->setRotationExplicit(0.0, 0.0, tmpUpdate*360.0);
	m_transform->setScaleExplicit(tmpUpdate, tmpUpdate, tmpUpdate);
}

void Game::Render()
{
	m_shader->Bind();
	m_shader->setUniform("transform", m_transform->getTransformation());
	TestMesh->Draw();
}
