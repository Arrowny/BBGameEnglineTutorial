#pragma once

#include "pointLight.h"
#include <glm\glm.hpp>

struct spotLight
{
	pointLight pointL;
	glm::fvec3 direction;
	float cutoff;

	spotLight(const pointLight& point = pointLight(), const glm::fvec3& direction = glm::fvec3(), float cutoff = 0) :
		pointL(point),
		direction(glm::normalize(direction)),
		cutoff(cutoff) 
		{}

};

