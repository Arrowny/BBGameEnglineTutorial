#include "physicsEngine.h"
#include "gameObject.h"
#include <time.h>


PhysicsEngine::PhysicsEngine(const float& delta)
{
	SetFloat("delta", delta);
	SetFloat("randomSeed", time(NULL));
}


PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::UpdatePhysics(GameObject* object)
{
	object->updatePhysicsAll(m_generalPhysics, this);
	GetFloat
}
