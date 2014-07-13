#include "gameObject.h"

void gameObject::AddChild(gameObject& child)
{
	m_children.push_back(&child);
}

void gameObject::AddComponent(gameComponent* component)
{
	m_components.push_back(component);
}

void gameObject::input(float delta)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->input(m_transform, delta);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->input(delta);
}

void gameObject::update(float delta)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->update(m_transform, delta);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->update(delta);
}

void gameObject::render(Shader* shader, renderingEngine* renderingEngine)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->render(m_transform, shader, renderingEngine);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->render(shader, renderingEngine);
}