#pragma once
#include <vector>
#include "Input.h"
#include "transform.h"
#include "camera.h"
#include "shader.h"
#include "renderingEngine.h"

class GameComponent;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void ProcessInput(Input* input, double delta);
	void Update(double delta);
	void Render(Shader* shader, RenderingEngine* renderingEngine);
	void addToRenderingEngine(RenderingEngine* renderingEngine);
	void addChild(GameObject* child) { m_children.push_back(child); }
	void addComponent(GameComponent* component);

	Transform* m_transform;

private:
	GameObject(const GameObject& other) {}
	void operator=(const GameObject& other) {}

	std::vector<GameObject*> m_children;
	std::vector<GameComponent*> m_components;
};

