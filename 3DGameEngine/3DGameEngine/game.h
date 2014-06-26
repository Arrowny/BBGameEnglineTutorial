#pragma once
#include "input.h"

class Game
{
public:
	Game();
	virtual ~Game();

	void ProcessInput(Input* &m_input);
	void Update();
	void Render();
};

