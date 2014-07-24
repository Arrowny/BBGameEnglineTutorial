#include "GameObject.h"
#include "GameComponent.h"

GameObject::GameObject()
{
	m_transform = Transform();
}


GameObject::~GameObject()
{
}

GameObject* GameObject::AddChild(GameObject* child)
{
	children.push_back(child);
	child->SetEngine(coreengine);
	child->GetTransform().SetParent(&m_transform);
	return this;
}

GameObject* GameObject::AddComponent(GameComponent* comp)
{
	components.push_back(comp);
	comp->SetParent(this);
	return this;
}

void GameObject::input(float delta)
{
	m_transform.Update();

	for each (GameComponent* comp in components)
		comp->input(delta);

	for each (GameObject* child in children)
		child->input(delta);
}

void GameObject::update(float delta)
{

	for each (GameComponent* comp in components)
		comp->update(delta);

	for each (GameObject* child in children)
		child->update(delta);
}

void GameObject::render(Shader* m_shader, RenderingEngine* renderingEngine)
{
	for each (GameComponent* comp in components)
		comp->render(m_shader, renderingEngine);

	for each (GameObject* child in children)
		child->render(m_shader, renderingEngine);
}

void GameObject::SetEngine(coreEngine* engine)
{
	if (coreengine != engine)
	{
		coreengine = engine;

		for each (GameComponent* comp in components)
			comp->AddToEngine(engine);

		for each (GameObject* child in children)
			child->SetEngine(engine);
	}
}