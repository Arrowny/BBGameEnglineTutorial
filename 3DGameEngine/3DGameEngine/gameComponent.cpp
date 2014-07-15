#include "gameComponent.h"
#include <iostream>
#include "gameObject.h"


GameComponent::GameComponent()
{
}


GameComponent::~GameComponent()
{
}

Transform* GameComponent::getTransform()
{ 
	return m_parent->m_transform;
}