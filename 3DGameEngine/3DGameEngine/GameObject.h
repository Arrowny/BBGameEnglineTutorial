#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "GameComponent.h"
#include "transform.h"

class RenderingEngine;
class Shader;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void input();
	void update();
	void render(Shader* m_shader, Camera* m_camera);

	void AddChild(GameObject& child);
	void AddComponent(GameComponent* component);

	inline Transform& GetTransform() { return m_transform; }
private:
	std::vector<GameObject*> children;
	std::vector<GameComponent*> components;

	Transform m_transform;
};

