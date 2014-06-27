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

void Game::update(){

	m_shader->Update();

}

void Game::render(){

	m_shader->Bind();
	m_mesh->Draw();

}