#include "texture.h"
#include <iostream>
#include <cassert>


Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		std::cerr << "Error: Texture loading error for file " + fileName << std::endl;
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}


Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind(const unsigned int& whichText)
{
	assert(whichText >= 0 && whichText <= 31);
	glActiveTexture(GL_TEXTURE0 + whichText);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
