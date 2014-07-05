#pragma once

#include <glm\glm.hpp>
#include "baseLight.h"

struct directionalLight
{
public:
	baseLight	m_base;
	glm::fvec3	m_direction;

	directionalLight(const baseLight& base = baseLight(), glm::fvec3 direction = glm::fvec3(0, 0, 0)):
		m_base(base),
		m_direction(glm::normalize(direction))
	{}

protected:
private:

};
