#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include <glm/glm.hpp>

struct Material
{
	Texture*	texture;
	glm::fvec4	color;
	float		specularIntensity;
	float		specularPower;

	Material() {};

	Material(Texture* texture, const glm::fvec4 color, float specularIntensity, float specularPower):
		texture(texture),
		color(color),
		specularIntensity(specularIntensity),
		specularPower(specularPower)
		{}

};

#endif