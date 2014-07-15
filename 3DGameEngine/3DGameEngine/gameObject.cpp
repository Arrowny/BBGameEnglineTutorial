#include "gameObject.h"
#include "gameComponent.h"

gameObject* gameObject::AddChild(gameObject* child)
{
	m_children.push_back(child);
	return this;
}

gameObject* gameObject::AddComponent(gameComponent* component)
{
	m_components.push_back(component);
	component->SetParent(this);
	return this;
}

void gameObject::input(float delta)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->input(delta);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->input(delta);
}

void gameObject::update(float delta)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->update(delta);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->update(delta);
}

void gameObject::render(Shader* shader, renderingEngine* renderingEngine)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->render(shader, renderingEngine);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->render(shader, renderingEngine);
}

void gameObject::AddToRenderingEngine(renderingEngine* renderingEngine)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->AddToRenderingEngine(renderingEngine);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->AddToRenderingEngine(renderingEngine);
}