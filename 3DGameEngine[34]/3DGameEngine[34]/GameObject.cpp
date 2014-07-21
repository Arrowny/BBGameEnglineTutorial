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

void GameObject::input()
{
	for each (GameComponent* comp in components)
		comp->input(m_transform);

	for each (GameObject* child in children)
		child->input();
}

void GameObject::update()
{

	for each (GameComponent* comp in components)
		comp->update(m_transform);

	for each (GameObject* child in children)
		child->update();
}

void GameObject::render(Shader* m_shader, Camera* m_camera)
{
	for each (GameComponent* comp in components)
		comp->render(m_shader, &m_transform, m_camera);

	for each (GameObject* child in children)
		child->render(m_shader,m_camera);
}