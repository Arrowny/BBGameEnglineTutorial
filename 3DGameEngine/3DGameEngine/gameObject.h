#pragma once
#include <vector>
#include "Input.h"
#include "gameComponent.h"
#include "transform.h"
#include "camera.h"
#include "shader.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void ProcessInput(Input* input, double delta);
	void Update(double delta);
	void Render(Shader* shader, Camera* camera);

	std::vector<GameObject*> m_children;
	std::vector<GameComponent*> m_components;
	Transform* m_transform;

private:
	GameObject(const GameObject& other) {}
	void operator=(const GameObject& other) {}
};

