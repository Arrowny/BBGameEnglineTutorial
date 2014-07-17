#include "gameObject.h"
#include <iostream>
#include "gameComponent.h"


GameObject::GameObject()
{
	m_transform = NULL;
}


GameObject::~GameObject()
{
}

void GameObject::ProcessInput(Input* input, double delta)
{
	
	for (unsigned int ii = 0; ii < m_components.size(); ii++)
	{
		m_components[ii]->ProcessInput(input, delta);
	}

	for (unsigned int ii = 0; ii < m_children.size(); ii++)
	{
		m_children[ii]->ProcessInput(input, delta);
	}

	if (m_transform != NULL)
	{
		m_transform->UpdateTRS();
	}
}

void GameObject::Update(double delta)
{
	if (m_transform != NULL)
	{ 
		for (unsigned int ii = 0; ii < m_components.size(); ii++)
		{
			m_components[ii]->Update(delta);
		}

		for (unsigned int ii = 0; ii < m_children.size(); ii++)
		{
			m_children[ii]->Update(delta);
		}
	}
	else
	{
		std::cerr << "Error: in GameObject Update() method. m_transform not initialized" << std::endl;
		exit(1);
	}
	
}

void GameObject::Render(Shader* shader, RenderingEngine* renderingEngine)
{
	if ( renderingEngine->getCamera() != NULL )
	{
		for (unsigned int ii = 0; ii < m_components.size(); ii++)
		{
			m_components[ii]->Render(shader, renderingEngine);
		}

		for (unsigned int ii = 0; ii < m_children.size(); ii++)
		{
			m_children[ii]->Render(shader, renderingEngine);
		}
	}
	else
	{
		std::cerr << "Error: in GameObject Render() method. Failure to initialize m_camera." << std::endl;
		exit(1);
	}
}

void GameObject::addToRenderingEngine(RenderingEngine* renderingEngine)
{
	for (unsigned int ii = 0; ii < m_components.size(); ii++)
	{ m_components[ii]->addToRenderingEngine(renderingEngine); }

	for (unsigned int ii = 0; ii < m_children.size(); ii++)
	{ m_children[ii]->addToRenderingEngine(renderingEngine); }
}

void GameObject::addChild(GameObject* child)
{ 
	child->m_transform->setParent(this->m_transform);
	m_children.push_back(child); 
}

void GameObject::addComponent(GameComponent* component)
{ 
	component->m_parent = this;
	m_components.push_back(component); 
}
