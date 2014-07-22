#pragma once
#include "Texture.h"
#include <glm/glm.hpp>
#include <map>

struct Material
{
public:
	std::map<std::string, Texture*> m_textureMap;
	std::map<std::string, glm::vec3> m_vectorMap;
	std::map<std::string, float> m_floatMap;
	//Texture* m_texture;
	//glm::fvec3 basic_color;
	//float specularIntensity;
	//float specularPower;
	Material::Material()
	{
		m_textureMap = std::map<std::string, Texture*>();
		m_vectorMap = std::map<std::string, glm::vec3>();
		m_floatMap = std::map<std::string, float>();
	}

	inline void AddTexture(const std::string& name, Texture* value) { m_textureMap.insert(std::pair<std::string, Texture*>(name, value)); }
	inline void AddVector(const std::string& name, glm::vec3 value) { m_vectorMap.insert(std::pair<std::string, glm::vec3>(name, value)); }
	inline void AddFloat(const std::string& name, float value) { m_floatMap.insert(std::pair<std::string, float>(name, value)); }

	inline Texture* GetTexture(const std::string& name) const
	{
		std::map<std::string, Texture*>::const_iterator it = m_textureMap.find(name);
		if (it != m_textureMap.end())
			return it->second;
		
		return 0;
	}

	inline glm::vec3 GetVector(const std::string& name) const
	{
		std::map<std::string, glm::vec3>::const_iterator it = m_vectorMap.find(name);
		if (it != m_vectorMap.end())
			return it->second;

		return glm::vec3(0, 0, 0);
	}


	inline float GetFloat(const std::string& name) const
	{
		std::map<std::string, float>::const_iterator it = m_floatMap.find(name);
		if (it != m_floatMap.end())
			return it->second;

		return 0;
	}
			//Material::Material(Texture* texture) :
			//	m_texture(texture) 
			//{
			//	basic_color = glm::vec3(1, 1, 1);
			//	specularIntensity = 2; specularPower = 32;
			//}

			//Material::Material(Texture* texture, glm::fvec3 color) :
			//	m_texture(texture),
			//	basic_color(color) 
			//{ 
			//	specularIntensity = 1; specularPower = 15;
			//}

			//Material::Material(Texture* texture, glm::fvec3 color, float specularIntensity, float specularExponent) :
			//	m_texture(texture),
			//	basic_color(color),
			//	specularIntensity(specularIntensity),
			//	specularPower(specularExponent) {}



			//inline Texture* GetTexture() { return m_texture; }
			//inline void SetTexture(Texture* texture) { m_texture = texture; }
			//inline glm::fvec3 GetColor() { return basic_color; }
			//inline void SetColor(glm::fvec3 color) { basic_color = color; }
		};

