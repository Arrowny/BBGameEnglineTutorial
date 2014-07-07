#include "texture.h"


Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	gltextureparameteri
	glTexImage2D(m)
	stbi_image_free(imageData);
}


Texture::~Texture()
{
}
