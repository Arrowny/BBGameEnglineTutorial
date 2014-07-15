#pragma once
#include "Input.h"
#include "window.h"
#include "transform.h"
#include "camera.h"

class RenderingEngine;
class Shader;

class GameComponent
{
public:
	GameComponent();
	virtual ~GameComponent();

	virtual void Init(Window* window, Transform* transform) {}
	virtual void ProcessInput(Input* input, Transform* transform, double delta) {}
	virtual void Update(Transform* transform, double delta) {}
	virtual void Render(Transform* transform, Shader* shader, RenderingEngine* renderingEngine) {}
	virtual void addToRenderingEngine(RenderingEngine* renderingEngine) {}
};

