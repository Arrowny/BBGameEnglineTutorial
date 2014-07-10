#pragma once
#include <glm/glm.hpp>
#include "BaseLight.h"

struct DirectionalLight
{
public:
	BaseLight base;
	glm::fvec3 direction;

	DirectionalLight() :
		base(BaseLight()),
		direction(glm::vec3(0, 0, 0))
	{}
	DirectionalLight(BaseLight base, glm::vec3 direction) :
		base(base),
		direction(direction)
	{
		direction = glm::normalize(direction);
	}

};