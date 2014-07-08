#pragma once
#include "input.h"
#include "shader.h"
#include "phongShader.h"
#include "transform.h"
#include "mesh.h"
#include "material.h"
#include "texture.h"
#include "vertex.h"
#include "timing.h"
#include "resourceLoader.h"
#include "camera.h"

class Game
{
public:
	Game(PhongShader* shader, double screenWidth, double screenHeight);
	virtual ~Game();

	void ProcessInput(Input* &m_input);
	void Update();
	void Render();

private:
	Game(const Game& other) {}
	void operator=(const Game& other) {}

	PhongShader* m_shader;
	Transform* m_worldTransform;
	Camera* m_camera;

};

