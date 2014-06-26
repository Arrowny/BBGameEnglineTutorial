#include "game.h"
#include <iostream>



Game::Game()
{
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

}
