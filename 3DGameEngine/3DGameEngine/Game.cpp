#include "Game.h"
#include "Input.h"

//Game::Game()
//{
//
//}

Game::Game(Mesh* mesh, Shader* shader) :
m_mesh(mesh),
m_shader(shader)
{}

Game::~Game()
{
}

void Game::input(){

}

void Game::update(){

}

void Game::render(){
	m_mesh->Draw();
}