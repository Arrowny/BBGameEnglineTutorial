#include "gameObject.h"

void gameObject::AddChild(gameObject& child)
{
	m_children.push_back(&child);
}

void gameObject::AddComponent(gameComponent* component)
{
	m_components.push_back(component);
}

void gameObject::input()
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->input(m_transform);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->input();
}

void gameObject::update()
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->update(m_transform);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->update();
}

void gameObject::render()
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->render(m_transform);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->render();
}