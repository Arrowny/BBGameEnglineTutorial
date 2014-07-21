#include "Game.h"

void Game::input(float delta){
	
	m_root.inputAll(delta);

}

void Game::update(float delta){

}

void Game::render(renderingEngine* renderingEngine)
{
	renderingEngine->Render(&m_root);
}