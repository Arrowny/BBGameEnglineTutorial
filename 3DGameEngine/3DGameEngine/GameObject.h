#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "GameComponent.h"
#include "transform.h"

#include <vector>
#include "Transform.h"
#include "GameComponent.h"
class RenderingEngine;
class GameObject
{
public:
	GameObject();
	~GameObject();

	void input();
	void update();
	void render(Shader* m_shader, RenderingEngine* renderingEngine);

	void AddChild(GameObject& child);
	void AddComponent(GameComponent* component);

	inline Transform& GetTransform() { return m_transform; }
private:
	std::vector<GameObject*> children;
	std::vector<GameComponent*> components;

	Transform m_transform;
};

