#pragma once
#include "input.h"
#include "window.h"
#include "gameObject.h"
#include "renderingEngine.h"

class Game
{
public:
	Game(){}
	virtual ~Game(){}

	virtual void Init(Window* window) = 0;
	virtual void ProcessInput(Input* &input, double delta)
	{
		m_root.ProcessInput(input, delta);
	}

	virtual void Update(double delta)
	{
		m_root.Update(delta);
	}
	
	virtual void Render(RenderingEngine* renderingEngine)
	{
		renderingEngine->RenderGameObject(&m_root);
	}

	virtual void addChild(GameObject* gameObject)
	{
		m_root.addChild(gameObject);
	}

	virtual void addComponent(GameComponent* gameCompenent)
	{
		m_root.addComponent(gameCompenent);
	}

private:
	Game(const Game& other) {}
	void operator=(const Game& other) {}

	GameObject m_root;
};

