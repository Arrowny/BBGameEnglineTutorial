#pragma once
#include "Input.h"
#include "window.h"
#include "transform.h"
#include "camera.h"
#include "shader.h"

class GameComponent
{
public:
	GameComponent();
	virtual ~GameComponent();

	virtual void Init(Window* window, Transform* transform) = 0;
	virtual void ProcessInput(Input* input, Transform* transform, double delta) = 0;
	virtual void Update(Transform* transform, double delta) = 0;
	virtual void Render(Transform* transform, Camera* camera, Shader* shader) = 0;

private:
	GameComponent(const GameComponent& other) {}
	void operator=(const GameComponent& other) {}
};

