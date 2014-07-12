#pragma once
#include <vector>
#include "Input.h"
#include "gameComponent.h"
#include "transform.h"
#include "camera.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void ProcessInput(Input* input);
	void Update();
	void Render();

	std::vector<GameObject*> m_children;
	std::vector<GameComponent*> m_components;
	Transform* m_transform;
	Camera* m_camera;
private:
	GameObject(const GameObject& other) {}
	void operator=(const GameObject& other) {}
};

