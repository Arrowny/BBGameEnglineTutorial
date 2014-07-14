#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <algorithm> 
#include "GameComponent.h"
#include "transform.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void input();
	void update();
	void render();

	void AddChild(GameObject child);
	void AddComponent(GameComponent* component);

	Transform GetTransform();
private:
	std::vector<GameObject> children;
	std::vector<GameComponent*> components;

	//GameComponent* m_componnet;
	//GameObject* m_gameObject;
	Transform transform;
};

