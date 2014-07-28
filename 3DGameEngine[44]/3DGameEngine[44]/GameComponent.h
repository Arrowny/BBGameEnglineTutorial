#ifndef GAMECOMPONENT_H_INCLUDED
#define GAMECOMPONENT_H_INCLUDED

#include "Transform.h"
#include "gameObject.h"

class renderingEngine;
class Shader;

class gameComponent
{
public:
	virtual ~gameComponent() {}

	virtual void input(float delta) {}
	virtual void update(float delta) {}
	virtual void render(Shader* shader, renderingEngine* renderingEngine) {}

	virtual void AddToRenderingEngine(renderingEngine* renderingEngine) {}

	inline void SetParent(gameObject* parent) { m_parent = parent; }
	inline Transform& GetTransform() { return m_parent->GetTransform(); }
	inline const Transform& GetTransform() const { return m_parent->GetTransform(); }

private:
	gameObject* m_parent = new gameObject();
};

#endif // GAMECOMPONENT_H_INCLUDED
