#pragma once
#include "input.h"
#include "shader.h"
#include "transform.h"

class Game
{
public:
	Game(Shader* shader);
	virtual ~Game();

	void ProcessInput(Input* &m_input);
	void Update();
	void Render();

private:
	Game(const Game& other) {}
	void operator=(const Game& other) {}

	Shader* m_shader;
	Transform* m_transform;

};

