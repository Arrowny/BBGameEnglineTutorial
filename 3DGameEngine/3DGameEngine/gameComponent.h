#pragma once
#include "Input.h"
#include "window.h"
#include "transform.h"

class RenderingEngine;
class Shader;
class GameObject;

class GameComponent
{
public:
	GameComponent();
	virtual ~GameComponent();

	virtual void Init(Window* window) {}
	virtual void ProcessInput(Input* input, double delta) {}
	virtual void Update( double delta) {}
	virtual void Render( Shader* shader, RenderingEngine* renderingEngine) {}
	virtual void addToRenderingEngine(RenderingEngine* renderingEngine) {}
	Transform* getTransform();  //convienence method

	GameObject* m_parent;
};

