#ifndef GAMECOMPONENT_H_INCLUDED
#define GAMECOMPONENT_H_INCLUDED

#include "Transform.h"
#include "gameObject.h"

class RenderingEngine;
class PhysicsEngine;
class Shader;

class GameComponent
{
public:
	virtual ~GameComponent() {}

	virtual void input(const Input& input, float delta) {}
	virtual void update(float delta) {}
	virtual void updatePhysics(Shader* shader, PhysicsEngine* physicsEngine) {}
	virtual void render(Shader* shader, RenderingEngine* renderingEngine) {}

	virtual void AddToEngine(CoreEngine* engine) {}

	inline void SetParent(GameObject* parent) { m_parent = parent; }
	inline Transform& GetTransform() { return m_parent->GetTransform(); }
	inline const Transform& GetTransform() const { return m_parent->GetTransform(); }

private:
	GameObject* m_parent = new GameObject();
};

#endif // GAMECOMPONENT_H_INCLUDED
