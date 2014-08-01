#include "physicsEngine.h"
#include "gameObject.h"


PhysicsEngine::PhysicsEngine()
{
}


PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::UpdatePhysics(GameObject* object)
{
	object->updatePhysicsAll(m_generalPhysics, this);
}
