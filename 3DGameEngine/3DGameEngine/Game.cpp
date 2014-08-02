#include "Game.h"
#include "physicsEngine.h"

void Game::input(const Input& input, float delta)
{
	m_root.inputAll(input, delta);
}

void Game::update(float delta)
{

}

void Game::updatePhysics(PhysicsEngine* physicsEngine)
{
	physicsEngine->UpdatePhysics(&m_root);
}

void Game::render(RenderingEngine* renderingEngine)
{
	renderingEngine->Render(&m_root);
}