#include "gameObject.h"
#include "gameComponent.h"

GameObject* GameObject::AddChild(GameObject* child)
{
	m_children.push_back(child);
	child->GetTransform().SetParent(&m_transform);
	child->SetEngine(m_coreEngine);
	return this;
}

GameObject* GameObject::AddComponent(GameComponent* component)
{
	m_components.push_back(component);
	component->SetParent(this);
	return this;
}

void GameObject::inputAll(const Input& gameInput, float delta)
{
	input(gameInput, delta);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->inputAll(gameInput, delta);

}

void GameObject::updateAll(float delta)
{
	update(delta);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->updateAll(delta);
}

void GameObject::updatePhysicsAll(Shader* shader, PhysicsEngine* physicsEngine)
{
	updatePhysics(shader, physicsEngine);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->updatePhysicsAll(shader, physicsEngine);
}

void GameObject::renderAll(Shader* shader, RenderingEngine* renderingEngine)
{
	render(shader, renderingEngine);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->renderAll(shader, renderingEngine);
}

void GameObject::input(const Input& input, float delta)
{
	m_transform.Update();

	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->input(input, delta);

}

void GameObject::update(float delta)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->update(delta);
}

void GameObject::updatePhysics(Shader* shader, PhysicsEngine* physicsEngine)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->updatePhysics(shader, physicsEngine);
}

void GameObject::render(Shader* shader, RenderingEngine* renderingEngine)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->render(shader, renderingEngine);
}

void GameObject::SetEngine(CoreEngine* engine)
{
	if (m_coreEngine != engine)
	{
		m_coreEngine = engine;

		for (unsigned int i = 0; i < m_components.size(); i++)
			m_components[i]->AddToEngine(engine);

		for (unsigned int i = 0; i < m_children.size(); i++)
			m_children[i]->SetEngine(engine);
	}
}

std::vector<GameObject*> GameObject::GetAllAttached()
{
	std::vector<GameObject*> result;

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		std::vector<GameObject*> childObjects = m_children[i]->GetAllAttached();
		result.insert(result.end(), childObjects.begin(), childObjects.end());
	}

	result.push_back(this);
	return result;
}