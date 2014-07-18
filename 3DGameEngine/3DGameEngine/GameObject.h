#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Transform.h"
class GameComponent;
class Shader;
class RenderingEngine;


class GameObject
{
public:
	GameObject();
	~GameObject();

	void input(float delta);
	void update(float delta);
	void render(Shader* m_shader, RenderingEngine* renderingEngine);

	void AddChild(GameObject& child);
	void AddComponent(GameComponent* component);

	void AddToRenderingEngine(RenderingEngine* renderingEngine);


	inline Transform& GetTransform() { return m_transform; }
private:
	std::vector<GameObject*> children;
	std::vector<GameComponent*> components;

	Transform m_transform;
};

