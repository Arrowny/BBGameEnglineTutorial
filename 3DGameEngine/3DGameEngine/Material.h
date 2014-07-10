#pragma once
#include "Texture.h"
#include <glm/glm.hpp>

struct Material
{
public:
	Texture* m_texture;
	glm::fvec3 basic_color;
	float specularIntensity;
	float specularPower;

	Material::Material(Texture* texture) :
		m_texture(texture) 
	{
		basic_color = glm::vec3(1, 1, 1);
		specularIntensity = 2; specularPower = 32;
	}

	Material::Material(Texture* texture, glm::fvec3 color) :
		m_texture(texture),
		basic_color(color) 
	{ 
		specularIntensity = 1; specularPower = 15;
	}

	Material::Material(Texture* texture, glm::fvec3 color, float specularIntensity, float specularExponent) :
		m_texture(texture),
		basic_color(color),
		specularIntensity(specularIntensity),
		specularPower(specularExponent) {}



	//inline Texture* GetTexture() { return m_texture; }
	//inline void SetTexture(Texture* texture) { m_texture = texture; }
	//inline glm::fvec3 GetColor() { return basic_color; }
	//inline void SetColor(glm::fvec3 color) { basic_color = color; }
};

