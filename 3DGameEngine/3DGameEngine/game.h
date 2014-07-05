#pragma once
#include "input.h"
#include "shader.h"
#include "transform.h"
#include "mesh.h"
#include "vertex.h"
#include "timing.h"
#include "resourceLoader.h"
#include "camera.h"

class Game
{
public:
	Game(Shader* shader, double screenWidth, double screenHeight);
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

