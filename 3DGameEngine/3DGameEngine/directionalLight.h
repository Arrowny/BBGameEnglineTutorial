#pragma once

#include <glm\glm.hpp>
#include "baseLight.h"
#include "gameComponent.h"

struct directionalLight : public gameComponent
{
	baseLight	m_base;
	glm::fvec3	m_direction;

	directionalLight(const baseLight& base = baseLight(), glm::fvec3 direction = glm::fvec3(0, 0, 0)):
		m_base(base),
		m_direction(glm::normalize(direction))
	{}

	virtual void AddToRenderingEngine(renderingEngine* renderingEngine);

};
