#pragma once
#include <glm/glm.hpp>

struct BaseLight
{
public:

	glm::vec3 color;
	float intensity;

	BaseLight() :
		color(glm::vec3(0, 0, 0)),
		intensity(1)
	{}
	BaseLight(glm::fvec3& color, float intensity) :
		color(color),
		intensity(intensity)
	{}

};

