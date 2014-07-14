#pragma once

#include "baseLight.h"
#include "Attenuation.h"
#include <glm\glm.hpp>
#include "gameComponent.h"

struct pointLight : public baseLight
{
	Attenuation atten;
	glm::fvec3 position;
	float range;

	pointLight(const glm::fvec3& color = glm::fvec3(0, 0, 0), float intensity = 0, const Attenuation& atten = Attenuation(), const glm::fvec3& position = glm::fvec3(), float range = 0);

};
