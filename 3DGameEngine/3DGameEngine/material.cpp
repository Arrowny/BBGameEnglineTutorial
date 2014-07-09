#include "material.h"


Material::Material(glm::vec3 color)
{
	m_texture = NULL;
	m_color = color;
}

Material::Material(const glm::vec3& color, const float& specularIntensity = 2, const float& specularPower = 32)
{
	m_texture = NULL;
	m_color = color;
	m_specularIntensity = specularIntensity;
	m_specularPower = specularPower;
}

Material::Material(const std::string& fileName, const glm::vec3& color, const float& specularIntensity = 2, const float& specularPower = 32)
{
	m_texture = new Texture(fileName);
	m_color = color;
	m_specularIntensity = specularIntensity;
	m_specularPower = specularPower;
}

Material::~Material()
{
}
