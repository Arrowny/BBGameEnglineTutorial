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
	gameObject() { m_coreEngine = 0; };
	virtual ~gameObject() {};

	gameObject* AddChild(gameObject* child);
	gameObject* AddComponent(gameComponent* component);

	void inputAll(const Input& input, float delta);
	void updateAll(float delta);
	void renderAll(Shader* shader, renderingEngine* renderingEngine);
	void SetEngine(coreEngine* engine);

	std::vector<gameObject*> GetAllAttached();

	inline Transform& GetTransform() { return m_transform; }

protected:
	void input(const Input& input, float delta);
	void update(float delta);
	void render(Shader* shader, renderingEngine* renderingEngine);

private:
	std::vector<gameObject*> m_children;
	std::vector<gameComponent*> m_components;
	Transform m_transform;
	coreEngine* m_coreEngine;

};

