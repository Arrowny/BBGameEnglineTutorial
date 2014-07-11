#pragma once
#include "Input.h"
#include "window.h"
#include "transform.h"

class GameComponent
{
public:
	GameComponent();
	virtual ~GameComponent();

	virtual void Init(Window* window, Transform transform) = 0;
	virtual void ProcessInput(Input* input, Transform transform) = 0;
	virtual void Update(Transform transform) = 0;
	virtual void Render(Transform transform) = 0;

private:
	GameComponent(const GameComponent& other) {}
	void operator=(const GameComponent& other) {}
};

