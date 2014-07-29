#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include <glm/glm.hpp>
#include <map>

struct Material
{
	Texture*	texture;
	glm::fvec4	color;
	float		specularIntensity;
	float		specularPower;

	Material():
		m_textureMap(std::map<std::string, Texture*>()),
		m_vec3fMap(std::map<std::string, glm::fvec3>()),
		m_floatMap(std::map<std::string, float>())
		{};

	Material(Texture* texture, const glm::fvec4 color, float specularIntensity, float specularPower) :
		m_textureMap(std::map<std::string, Texture*>()),
		m_vec3fMap(std::map<std::string, glm::fvec3>()),
		m_floatMap(std::map<std::string, float>())
		{};

	inline void AddTexture(const std::string& name, Texture* value) { m_textureMap.insert(std::pair<std::string, Texture*>(name, value)); }
	inline void AddVector3f(const std::string& name, glm::fvec3 value) { m_vec3fMap.insert(std::pair<std::string, glm::fvec3>(name, value)); }
	inline void AddFloat(const std::string& name, float value) { m_floatMap.insert(std::pair<std::string, float>(name, value)); }

	Texture* GetTexture(const std::string& name) const;
	glm::fvec3 GetVector3f(const std::string& name) const;
	float GetFloat(const std::string& name) const;

private:
	std::map<std::string, Texture*> m_textureMap;
	std::map<std::string, glm::fvec3> m_vec3fMap;
	std::map<std::string, float> m_floatMap;

};

#endif