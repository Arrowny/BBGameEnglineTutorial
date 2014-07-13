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
	//float range;

	PointLight() :
		base(BaseLight()),
		atten(Attenuation()),
		position(glm::fvec3(0.0,0.0,0.0))
		//range(50.0)
	{}


	PointLight(BaseLight baselight, Attenuation attenu, glm::fvec3 position, float range) :
		base(baselight),
		atten(attenu),
		position(position)
	//	range(range)
	{}

	void SetPosition(glm::vec3 pos) { position = pos; }
	//void SetRange(float ran) { range = ran; }
};