#pragma once

#include <vector>
#include "gameComponent.h"
#include "Transform.h"
#include "Shader.h"

class gameObject
{
public:
	gameObject() {};

	void AddChild(gameObject& child);
	void AddComponent(gameComponent* component);

	void input();
	void update();
	void render(Shader* shader);

protected:
private:
	std::vector<gameObject*> m_children;
	std::vector<gameComponent*> m_components;
	Transform m_transform;

};

