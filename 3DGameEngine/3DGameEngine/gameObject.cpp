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

void gameObject::inputAll(const Input& gameInput, float delta)
{
	input(gameInput, delta);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->inputAll(gameInput, delta);

}

void gameObject::updateAll(float delta)
{
	update(delta);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->updateAll(delta);
}

void gameObject::renderAll(Shader* shader, renderingEngine* renderingEngine)
{
	render(shader, renderingEngine);

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->renderAll(shader, renderingEngine);
}

void gameObject::input(const Input& input, float delta)
{
	m_transform.Update();

	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->input(input, delta);

}

void gameObject::update(float delta)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->update(delta);
}

void gameObject::render(Shader* shader, renderingEngine* renderingEngine)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->render(shader, renderingEngine);
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

std::vector<gameObject*> gameObject::GetAllAttached()
{
	std::vector<gameObject*> result;

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		std::vector<gameObject*> childObjects = m_children[i]->GetAllAttached();
		result.insert(result.end(), childObjects.begin(), childObjects.end());
	}

	result.push_back(this);
	return result;
}