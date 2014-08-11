#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>
#include "Texture.h"

class Texture3D : public Texture
{
public:
	Texture3D(GLsizei texWidth, GLsizei texHeight, GLsizei texDepth, std::vector<glm::vec3> data);
	virtual ~Texture3D();

	virtual void Bind(unsigned int unit) const;

private:
	Texture3D(const Texture3D& other) {}
	void operator=(const Texture3D& other) {}

	GLsizei m_texWidth;
	GLsizei m_texHeight;
	GLsizei m_texDepth;

};

