#pragma once

#include <glm\glm.hpp>
#include "texture.h"

class Material
{
public:
	Material(glm::vec3 color);
	Material(const std::string& fileName, glm::vec3 color);
	virtual ~Material();

	Texture* m_texture;
	glm::vec3 m_color;

private:
	Material(const Material& other) {}
	void operator=(const Material& other) {}
};

