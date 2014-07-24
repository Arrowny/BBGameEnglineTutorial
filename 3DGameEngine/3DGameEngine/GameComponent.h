#pragma once

#include "Transform.h"
#include "GameObject.h"
class RenderingEngine;
class Shader;


class GameComponent
{
public:

	virtual void input(float delta) {}
	virtual void update(float delta) {}
	virtual void render(Shader* m_shader,RenderingEngine* renderingEngine) {}

	virtual void AddToRenderingEngine(RenderingEngine* renderingEnine){}

	inline void SetParent(GameObject* parent) { m_parent = parent; }
	inline Transform& GetTransform() { return m_parent->GetTransform(); }
	inline const Transform& GetTransform() const { return m_parent->GetTransform(); }

	virtual void AddToEngine(coreEngine* engine) {}
	virtual ~GameComponent() {};

private:
	GameObject* m_parent;
};

