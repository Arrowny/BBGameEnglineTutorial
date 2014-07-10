#pragma once
#include "game.h"
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

class TestGame :
	public Game
{
public:
	TestGame() {}
	virtual ~TestGame();

	virtual void Init(Window* window) override;
	virtual void ProcessInput(Input* &m_input) override;
	virtual void Update() override;
	virtual void Render() override;

private:
	TestGame(const TestGame& other) {}
	void operator=(const TestGame& other) {}

	PhongShader* m_shader;
	Transform* m_worldTransform;
	Camera* m_camera;
};

