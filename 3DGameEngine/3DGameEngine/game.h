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
	virtual void ProcessInput(Input* &input)
	{
		m_root.ProcessInput(input);
	}

	virtual void Update()
	{
		m_root.Update();
	}

	GameObject m_root;

private:
	Game(const Game& other) {}
	void operator=(const Game& other) {}
};

