#include "gameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::ProcessInput(Input* input)
{
	for (int ii = 0; ii < m_children.size(); ii++)
	{
		m_components[ii]->ProcessInput(input, m_transform);
	}

	for (int ii = 0; ii < m_children.size(); ii++)
	{
		m_children[ii]->ProcessInput(input);
	}
}

void GameObject::Update()
{
	for (int ii = 0; ii < m_children.size(); ii++)
	{
		m_components[ii]->Update(m_transform);
	}

	for (int ii = 0; ii < m_children.size(); ii++)
	{
		m_children[ii]->Update();
	}
}

void GameObject::Render()
{
	for (int ii = 0; ii < m_components.size(); ii++)
	{
		m_components[ii]->Render(m_transform, m_camera);
	}

	for (int ii = 0; ii < m_children.size(); ii++)
	{
		m_children[ii]->Render();
	}
}
