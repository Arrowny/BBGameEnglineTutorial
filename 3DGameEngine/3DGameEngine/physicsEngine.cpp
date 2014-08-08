#include "physicsEngine.h"
#include "gameObject.h"
#include "Util.h"


PhysicsEngine::PhysicsEngine(const float& delta)
{

	SetFloat("delta", delta);
	SetVector3f("randomSeed", Util::randomVec3());

	m_samplerMap["vectorField"] = 0; //set slot for baseVectorField
	//add more vectorfields if needed
}


PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::UpdatePhysics(GameObject* object)
{
	object->updatePhysicsAll(m_generalPhysics, this);
	SetVector3f("randomSeed", Util::randomVec3());
}
