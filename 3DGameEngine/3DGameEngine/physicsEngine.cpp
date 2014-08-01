#include "physicsEngine.h"
#include "gameObject.h"


PhysicsEngine::PhysicsEngine(const float& delta)
{
	AddFloat("delta", delta);
}


PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::UpdatePhysics(GameObject* object, float delta)
{
	object->updatePhysicsAll(m_generalPhysics, this, delta);
}
