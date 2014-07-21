#include "gameObject.h"
#include "gameComponent.h"

gameObject* gameObject::AddChild(gameObject* child)
{
	m_children.push_back(child);
	child->GetTransform().SetParent(&m_transform);
	child->SetEngine(m_coreEngine);
	return this;
}

gameObject* gameObject::AddComponent(gameComponent* component)
{
	m_components.push_back(component);
	component->SetParent(this);
	return this;
}

void gameObject::ProcessInput(const Input& input, float delta)
{
	ProcessInput(input, delta);

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->ProcessInput(input, delta);
	}
}

void gameObject::input(float delta)
{
	m_transform.Update();

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

void gameObject::SetEngine(coreEngine* engine)
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
