#pragma once
#include "Texture.h"
#include <glm/glm.hpp>

struct Material
{
public:
	Texture* m_texture;
	glm::fvec3 basic_color;

	Material::Material(Texture* texture, glm::fvec3 color) :
		m_texture(texture),
		basic_color(color)
	{}

	//inline Texture* GetTexture() { return m_texture; }
	//inline void SetTexture(Texture* texture) { m_texture = texture; }
	//inline glm::fvec3 GetColor() { return basic_color; }
	//inline void SetColor(glm::fvec3 color) { basic_color = color; }
};

