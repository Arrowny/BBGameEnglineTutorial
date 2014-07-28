#pragma once

#include "pointLight.h"
#include <glm\glm.hpp>

struct spotLight : public pointLight
{
	glm::fvec3 direction;
	float cutoff;

	spotLight(const glm::fvec3& color = glm::fvec3(0, 0, 0), float intensity = 0, const Attenuation& atten = Attenuation(), float cutoff = 0);

};

