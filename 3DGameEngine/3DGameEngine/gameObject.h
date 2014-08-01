#pragma once

#include <vector>
#include "Transform.h"
#include "input.h"

class CoreEngine;
class GameComponent;
class Shader;
class RenderingEngine;
class PhysicsEngine;

class GameObject
{
public:
	GameObject() { m_coreEngine = 0; };
	virtual ~GameObject() {};

	GameObject* AddChild(GameObject* child);
	GameObject* AddComponent(GameComponent* component);

	void inputAll(const Input& input, float delta);
	void updateAll(float delta);
	void updatePhysicsAll(Shader* shader, PhysicsEngine* physicsEngine, float delta);
	void renderAll(Shader* shader, RenderingEngine* renderingEngine);
	void SetEngine(CoreEngine* engine);

	std::vector<GameObject*> GetAllAttached();

	inline Transform& GetTransform() { return m_transform; }

protected:
	void input(const Input& input, float delta);
	void update(float delta);
	void updatePhysics(Shader* shader, PhysicsEngine* physicsEngine, float delta);
	void render(Shader* shader, RenderingEngine* renderingEngine);

private:
	std::vector<GameObject*> m_children;
	std::vector<GameComponent*> m_components;
	Transform m_transform;
	CoreEngine* m_coreEngine;

};

