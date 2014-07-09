#include "material.h"


Material::Material(glm::vec3 color)
{
	m_texture = NULL;
	m_color = color;
}

Material::Material(const std::string& fileName, const glm::vec3& color)
{
	m_texture = new Texture(fileName);
	m_color = color;
	m_specularIntensity = 2;
	m_specularPower = 32;
}

Material::Material(const std::string& fileName, const glm::vec3& color, const float& specularIntensity, const float& specularPower)
{
	m_texture = new Texture(fileName);
	m_color = color;
	m_specularIntensity = specularIntensity;
	m_specularPower = specularPower;
}

Material::~Material()
{
}
