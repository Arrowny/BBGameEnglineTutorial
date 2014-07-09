#pragma once

#include <glm\glm.hpp>
#include "texture.h"

class Material
{
public:
	Material(glm::vec3 color);
	Material(const std::string& fileName, const glm::vec3& color);
	Material(const std::string& fileName, const glm::vec3& color, const float& specularIntensity, const float& specularPower);
	virtual ~Material();

	Texture* m_texture;
	glm::vec3 m_color;
	float m_specularIntensity;
	float m_specularPower;

private:
	Material(const Material& other) {}
	void operator=(const Material& other) {}
};

