#pragma once

#include <glm\glm.hpp>

struct baseLight
{
public:
	glm::fvec3	m_color;
	float	m_intensity;

	baseLight(const glm::fvec3& color = glm::fvec3(0, 0, 0), float intensity = 0):
		m_color(color),
		m_intensity(intensity)
	{
	}

protected:
private:
	

};

