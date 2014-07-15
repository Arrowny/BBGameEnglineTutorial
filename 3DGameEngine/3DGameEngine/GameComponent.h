#pragma once
#include "transform.h"
#include "Shader.h"
#include "Camera.h"

class GameComponent
{
public:

	virtual void input(Transform transform) {}
	virtual void update(Transform transform) {}
	virtual void render(Transform* m_transform, Camera* m_camera) {}
//	virtual ~GameComponent() {};

	//void input(Transform transform);
	//void update(Transform transform);
	//void render(Transform transform);

};

