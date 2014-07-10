#pragma once
#include <glm/glm.hpp>
#include "BaseLight.h"
#include "Attenuation.h"


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

struct PointLight
{
	BaseLight base;
	Attenuation atten;
	glm::fvec3 position;

	PointLight() :
		base(BaseLight()),
		atten(Attenuation()),
		position(glm::fvec3(0.0,0.0,0.0))
	{}


	PointLight(BaseLight baselight, Attenuation attenu, glm::fvec3 position) :
		base(baselight),
		atten(attenu),
		position(position)
	{}
};