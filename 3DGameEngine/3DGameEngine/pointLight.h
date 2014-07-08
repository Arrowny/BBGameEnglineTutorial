#pragma once

#include "baseLight.h"
#include "Attenuation.h"
#include <glm\glm.hpp>

struct pointLight
{
	baseLight base;
	Attenuation atten;
	glm::fvec3 position;
	float range;

	pointLight(const baseLight& base = baseLight(), const Attenuation& atten = Attenuation(), glm::fvec3& position = glm::fvec3(), float range = 0) :
		base(base),
		atten(atten),
		position(position),
		range(range) {}

	void setPos(glm::fvec3 position)
	{
		this->position = position;
	}

	glm::fvec3 getPos()
	{
		return position;
	}

};
