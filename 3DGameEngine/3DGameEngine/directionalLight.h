#pragma once
#include <glm\glm.hpp>
#include "baseLight.h"

struct DirectionalLight
{
public:
	DirectionalLight() :
		m_base(BaseLight()),
		m_direction(glm::vec3(0,0,0))
	{}
	DirectionalLight(BaseLight base, glm::vec3 direction) :
		m_base(base),
		m_direction(glm::normalize(direction)) {}
	virtual ~DirectionalLight() {}

	BaseLight m_base;
	glm::vec3 m_direction;
};