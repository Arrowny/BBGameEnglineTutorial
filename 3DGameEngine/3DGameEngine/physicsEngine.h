#pragma once

class GameObject;
class Shader;

class PhysicsEngine
{
public:
	PhysicsEngine();
	virtual ~PhysicsEngine();

	void UpdatePhysics(GameObject* object);

private:
	Shader* m_generalPhysics; //TODO: no general physics implemented yet
};

