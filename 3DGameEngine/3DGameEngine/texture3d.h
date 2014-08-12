#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>
#include "Texture.h"

class Texture3D : public Texture
{
public:
	Texture3D(GLsizei texWidth, GLsizei texHeight, GLsizei texDepth, std::vector<glm::vec3> data);
	Texture3D(GLsizei texWidth, GLsizei texHeight, GLsizei texDepth, std::vector<float> data);
	virtual ~Texture3D();

	virtual void Bind(unsigned int unit) const;

	GLuint GetHandle() { return m_texture; }
	GLsizei GetTexWidth() { return m_texWidth; }
	GLsizei GetTexHeight() { return m_texHeight; }
	GLsizei GetTexDepth() { return m_texDepth; }

private:
	Texture3D(const Texture3D& other) {}
	void operator=(const Texture3D& other) {}

	GLsizei m_texWidth;
	GLsizei m_texHeight;
	GLsizei m_texDepth;

};

