#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include <glm/glm.hpp>

struct Material
{
	Texture* texture;
	glm::fvec4 color;

	Material() {};

	Material(Texture* texture, const glm::fvec4 color):
		texture(texture),
		color(color)
		{}
};

#endif