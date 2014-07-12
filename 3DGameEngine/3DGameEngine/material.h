#pragma once

#include <glm\glm.hpp>
#include "texture.h"

class Material
{
public:
	Material() :
		m_color(glm::vec3(0,0,0)),
		m_specularIntensity(0),
		m_specularPower(0) {}
	Material(glm::vec3 color);
	Material(const glm::vec3& color, const float& specularIntensity, const float& specularPower);
	Material(const std::string& fileName, const glm::vec3& color, const float& specularIntensity, const float& specularPower);
	virtual ~Material();

	Texture* m_texture;
	glm::vec3 m_color;
	float m_specularIntensity;
	float m_specularPower;
};

