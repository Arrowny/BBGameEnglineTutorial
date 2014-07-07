#include "material.h"


Material::Material(glm::vec3 color)
{
	m_texture = NULL;
	m_color = color;
}

Material::Material(const std::string& fileName, glm::vec3 color)
{
	m_texture = new Texture(fileName);
	m_color = color;
}


Material::~Material()
{
}
