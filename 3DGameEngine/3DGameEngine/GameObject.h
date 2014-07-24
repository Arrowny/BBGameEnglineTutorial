#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Transform.h"
class coreEngine;
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

	GameObject* AddChild(GameObject* child);
	GameObject* AddComponent(GameComponent* component);

	void SetEngine(coreEngine* engine);


	inline Transform& GetTransform() { return m_transform; }
private:
	std::vector<GameObject*> children;
	std::vector<GameComponent*> components;

	Transform m_transform;
	coreEngine* coreengine = nullptr;
};

