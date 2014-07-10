#pragma once

#include <vector>
#include "gameComponent.h"
#include "Transform.h"
#include "Shader.h"
#include "renderingEngine.h"

class gameObject
{
public:
	gameObject() {};

	void AddChild(gameObject& child);
	void AddComponent(gameComponent* component);

	void input();
	void update();
	void render(Shader* shader, renderingEngine* renderingEngine);

	inline Transform& GetTransform() { return m_transform; }
protected:
private:
	std::vector<gameObject*> m_children;
	std::vector<gameComponent*> m_components;
	Transform m_transform;

};

