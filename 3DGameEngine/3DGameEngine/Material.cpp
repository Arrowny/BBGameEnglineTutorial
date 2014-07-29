#include "Material.h"

Texture* Material::GetTexture(const std::string& name) const
{
	std::map<std::string, Texture*>::const_iterator it = m_textureMap.find(name);
	if (it != m_textureMap.end())
		return it->second;

	return 0;
}

glm::fvec3 Material::GetVector3f(const std::string& name) const
{
	std::map<std::string, glm::fvec3>::const_iterator it = m_vec3fMap.find(name);
	if (it != m_vec3fMap.end())
		return it->second;

	return glm::fvec3(0, 0, 0);
}

float Material::GetFloat(const std::string& name) const
{
	std::map<std::string, float>::const_iterator it = m_floatMap.find(name);
	if (it != m_floatMap.end())
		return it->second;

	return 0;
}