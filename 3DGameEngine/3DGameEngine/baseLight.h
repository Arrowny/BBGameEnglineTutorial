#pragma once
#include <glm\glm.hpp>

struct BaseLight
{
public:
	BaseLight() :
		m_color(glm::vec3(1,1,1)),
		m_intensity(0.0) {}
	BaseLight(glm::vec3 color, float intensity) :
		m_color(color),
		m_intensity(intensity) {}
	virtual ~BaseLight() {}

	glm::vec3 m_color;
	GLfloat m_intensity;
};

