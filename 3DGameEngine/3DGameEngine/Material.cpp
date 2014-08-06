#include "Material.h"
#include "Texture.h"

Material::Material(Texture* texture, float specularIntensity, float specularPower, float quadLength) :
m_textureMap(std::unordered_map<std::string, Texture*>()),
m_vec3fMap(std::unordered_map<std::string, glm::fvec3>()),
m_floatMap(std::unordered_map<std::string, float>()),
m_intMap(std::unordered_map<std::string, int>())
{
	AddTexture("diffuse", texture);
	AddFloat("specularIntensity", specularIntensity);
	AddFloat("specularPower", specularPower);
};

Texture* Material::GetTexture(const std::string& name) const
{
	std::unordered_map<std::string, Texture*>::const_iterator it = m_textureMap.find(name);
	if (it != m_textureMap.end())
		return it->second;

	return 0;
}

glm::fvec3 Material::GetVector3f(const std::string& name) const
{
	std::unordered_map<std::string, glm::fvec3>::const_iterator it = m_vec3fMap.find(name);
	if (it != m_vec3fMap.end())
		return it->second;

	return glm::fvec3(0.0, 0.0, 0.0);
}

float Material::GetFloat(const std::string& name) const
{
	std::unordered_map<std::string, float>::const_iterator it = m_floatMap.find(name);
	if (it != m_floatMap.end())
		return it->second;

	return 0;
}

int Material::GetInt(const std::string& name) const
{
	std::unordered_map<std::string, int>::const_iterator it = m_intMap.find(name);
	if (it != m_intMap.end())
		return it->second;

	return 0;
}