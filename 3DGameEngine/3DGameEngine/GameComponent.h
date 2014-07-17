#pragma once

#include "Transform.h"
class RenderingEngine;
class Shader;


class GameComponent
{
public:

	virtual void input(Transform transform) {}
	virtual void update(Transform transform) {}
	virtual void render(Shader* m_shader, Transform* m_transform, RenderingEngine* renderingEngine) {}
//	virtual ~GameComponent() {};

	//void input(Transform transform);
	//void update(Transform transform);
	//void render(Transform transform);

};

