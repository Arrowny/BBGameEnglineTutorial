#pragma once
#include "input.h"
#include "window.h"

class Game
{
public:
	Game(){}
	virtual ~Game(){}

	virtual void Init(Window* window) = 0;
	virtual void ProcessInput(Input* &m_input) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

private:
	Game(const Game& other) {}
	void operator=(const Game& other) {}


};

