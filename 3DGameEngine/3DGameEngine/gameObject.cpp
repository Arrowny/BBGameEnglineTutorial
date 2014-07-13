#include "gameObject.h"
#include <iostream>


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::ProcessInput(Input* input)
{
	for (int ii = 0; ii < m_components.size(); ii++)
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
	if (m_transform != NULL)
	{ 
		for (int ii = 0; ii < m_components.size(); ii++)
		{
			m_components[ii]->Update(m_transform);
		}

		for (int ii = 0; ii < m_children.size(); ii++)
		{
			m_children[ii]->Update();
		}
	}
	else
	{
		std::cerr << "Error: in GameObject Update() method. m_transform not initialized" << std::endl;
		exit(1);
	}
	
}

void GameObject::Render(Shader* shader)
{
	if (m_transform != NULL && m_camera != NULL)
	{
		for (int ii = 0; ii < m_components.size(); ii++)
		{
			m_components[ii]->Render(m_transform, m_camera, shader);
		}

		for (int ii = 0; ii < m_children.size(); ii++)
		{
			m_children[ii]->Render(shader);
		}
	}
	else
	{
		std::cerr << "Error: in GameObject Render() method. Failure to initialize m_camera or m_transform" << std::endl;
		exit(1);
	}

}
