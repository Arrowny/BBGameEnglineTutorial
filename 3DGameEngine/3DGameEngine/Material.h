#ifndef MATERIAL_H
#define MATERIAL_H


#include <glm/glm.hpp>
#include <unordered_map>

class Texture;

struct Material
{
	Material():
		m_textureMap(std::unordered_map<std::string, Texture*>()),
		m_vec3fMap(std::unordered_map<std::string, glm::fvec3>()),
		m_floatMap(std::unordered_map<std::string, float>()),
		m_intMap(std::unordered_map<std::string, int>())
		{};

	Material(Texture* texture, float specularIntensity, float specularPower, float quadLength = 0.1);

	inline void SetTexture(const std::string& name, Texture* value) { m_textureMap[name] = value; }
	inline void SetVector3f(const std::string& name, glm::fvec3 value) { m_vec3fMap[name] = value; }
	inline void SetFloat(const std::string& name, float value) { m_floatMap[name] = value; }
	inline void SetInt(const std::string& name, float value) { m_floatMap[name] = value; }

	Texture* GetTexture(const std::string& name) const;
	glm::fvec3 GetVector3f(const std::string& name) const;
	float GetFloat(const std::string& name) const;
	int GetInt(const std::string& name) const;

private:
	Texture*	texture;
	glm::fvec4	color;
	float		specularIntensity;
	float		specularPower;

	std::unordered_map<std::string, Texture*> m_textureMap;
	std::unordered_map<std::string, glm::fvec3> m_vec3fMap;
	std::unordered_map<std::string, float> m_floatMap;
	std::unordered_map<std::string, int> m_intMap;
};

#endif