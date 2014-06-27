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

	transform.GetPos().x = sinCounter;

	m_shader->Update(transform);
	counter += 0.0001f;

}

void Game::render(){

	m_shader->Bind();
	m_mesh->Draw();

}