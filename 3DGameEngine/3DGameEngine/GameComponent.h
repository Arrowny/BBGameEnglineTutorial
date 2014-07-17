#pragma once

#include "Transform.h"
class RenderingEngine;
class Shader;


class GameComponent
{
public:

	virtual void input(Transform transform, float delta) {}
	virtual void update(Transform transform, float delta) {}
	virtual void render(Shader* m_shader, Transform* m_transform, RenderingEngine* renderingEngine) {}
	virtual ~GameComponent() {};
};

