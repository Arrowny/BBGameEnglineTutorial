#pragma once
#include "Texture.h"
#include <glm/glm.hpp>


class Material
{
public:
	Material(Texture* texture, glm::fvec3 color) :
		m_texture(texture),
		m_color(color)
	{}

	inline glm::fvec3 GetColor() { return m_color; }
	inline void SetColor(glm::fvec3 color)	{ m_color = color; }

	~Material();


private:
	Texture* m_texture;
	glm::fvec3 m_color;
};

