#pragma once

class GameObject;
class PhysicsEngine
{
public:
	PhysicsEngine();
	virtual ~PhysicsEngine();

	void UpdatePhysics(GameObject* object);

};

