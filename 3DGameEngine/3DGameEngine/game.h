#pragma once
#include "input.h"
#include "window.h"
#include "gameObject.h"

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

	GameObject m_root;

private:
	Game(const Game& other) {}
	void operator=(const Game& other) {}
};

