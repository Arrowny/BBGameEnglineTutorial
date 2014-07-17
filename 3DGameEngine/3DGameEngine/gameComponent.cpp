#include "gameComponent.h"
#include <iostream>
#include "gameObject.h"


GameComponent::GameComponent()
{
	m_parent = NULL;
}


GameComponent::~GameComponent()
{
}

Transform* GameComponent::getTransform()
{ 

	return m_parent->m_transform;
}