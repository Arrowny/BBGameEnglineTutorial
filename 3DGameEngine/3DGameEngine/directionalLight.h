#pragma once

#include <glm\glm.hpp>
#include "baseLight.h"
#include "gameComponent.h"

struct directionalLight : public baseLight
{
	glm::fvec3 direction;

	directionalLight(const glm::fvec3& color = glm::fvec3(0, 0, 0), float intensity = 0, const glm::fvec3& direction = glm::fvec3(0, 0, 0));

};
