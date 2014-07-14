#pragma once

#include <vector>
#include "gameComponent.h"
#include "Transform.h"

class renderingEngine;

class gameObject
{
public:
	gameObject() {};

	void AddChild(gameObject& child);
	void AddComponent(gameComponent* component);

	void input(float delta);
	void update(float delta);
	void render(Shader* shader, renderingEngine* renderingEngine);
	void AddToRenderingEngine(renderingEngine* renderingEngine);

	inline Transform& GetTransform() { return m_transform; }
protected:
private:
	std::vector<gameObject*> m_children;
	std::vector<gameComponent*> m_components;
	Transform m_transform;

};

