#pragma once

#include <vector>
#include "Transform.h"
#include "input.h"

class coreEngine;
class gameComponent;
class Shader;
class renderingEngine;

class gameObject
{
public:
	gameObject() {};

	gameObject* AddChild(gameObject* child);
	gameObject* AddComponent(gameComponent* component);

	void ProcessInput(const Input& input, float delta);
	void input(float delta);
	void update(float delta);
	void render(Shader* shader, renderingEngine* renderingEngine);
	void AddToRenderingEngine(renderingEngine* renderingEngine);

	inline Transform& GetTransform() { return m_transform; }
	void SetEngine(coreEngine* engine);
protected:
private:
	std::vector<gameObject*> m_children;
	std::vector<gameComponent*> m_components;
	Transform m_transform;
	coreEngine* m_coreEngine;

};

