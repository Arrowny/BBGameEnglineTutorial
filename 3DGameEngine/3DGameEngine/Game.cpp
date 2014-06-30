#include "Game.h"

Game::Game(Mesh* mesh, Shader* shader):
m_mesh(mesh),
m_shader(shader)
{
}


Game::~Game()
{
}

void Game::input(){

}

float counter = 0.0f;

void Game::update(){

	float sinCounter = sinf(counter);
	float cosCounter = cosf(counter);

	transform.GetPos().z = -3.0;
	transform.GetRot().y = counter * 50;
	//transform.SetScale(glm::vec3(0.1f , 0.1f, 0.1f));

	m_shader->Update(transform);
	counter += 0.0003f;

}

void Game::render(){

	m_shader->Bind();
	m_mesh->Draw();

}