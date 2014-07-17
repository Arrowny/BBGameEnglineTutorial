#include "GameObject.h"


GameObject::GameObject()
{
	m_transform = Transform();
}


GameObject::~GameObject()
{
}

void GameObject::AddChild(GameObject& child)
{
	children.push_back(&child);
}

void GameObject::AddComponent(GameComponent* comp)
{
	components.push_back(comp);
}

void GameObject::input(float delta)
{
	for each (GameComponent* comp in components)
		comp->input(m_transform, delta);

	for each (GameObject* child in children)
		child->input(delta);
}

void GameObject::update(float delta)
{

	for each (GameComponent* comp in components)
		comp->update(m_transform, delta);

	for each (GameObject* child in children)
		child->update(delta);
}

void GameObject::render(Shader* m_shader, RenderingEngine* renderingEngine)
{
	for each (GameComponent* comp in components)
		comp->render(m_shader, &m_transform, renderingEngine);

	for each (GameObject* child in children)
		child->render(m_shader, renderingEngine);
}
