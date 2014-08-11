#include "texture3D.h"


Texture3D::Texture3D(GLsizei texWidth, GLsizei texHeight, GLsizei texDepth, std::vector<glm::vec3> data)
{
	m_texWidth = texWidth;
	m_texHeight = texHeight;
	m_texDepth = texDepth;
	
	if (texWidth > 0 && texHeight > 0 && texDepth > 0 && !data.empty())
	{
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_3D, m_texture);

		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB16F, texWidth, texHeight, texDepth, 0, GL_RGB, GL_FLOAT, &data[0]);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
}

Texture3D::Texture3D(GLsizei texWidth, GLsizei texHeight, GLsizei texDepth, std::vector<float> data)
{
	m_texWidth = texWidth;
	m_texHeight = texHeight;
	m_texDepth = texDepth;

	if (texWidth > 0 && texHeight > 0 && texDepth > 0 && !data.empty())
	{
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_3D, m_texture);

		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB16F, texWidth, texHeight, texDepth, 0, GL_RGB, GL_FLOAT, &data[0]);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
}


Texture3D::~Texture3D()
{
	glDeleteTextures(1, &m_texture);
}

void Texture3D::Bind(unsigned int unit) const
{
	assert(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_3D, m_texture);
}
