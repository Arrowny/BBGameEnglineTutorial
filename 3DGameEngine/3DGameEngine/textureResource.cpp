#include "textureResource.h"


TextureResource::TextureResource()
{
	glGenTextures(1, &m_texture);
}

TextureResource::~TextureResource()
{
	glDeleteTextures(1, &m_texture);
}

GLuint* TextureResource::getTexture()
{
	return &m_texture;
}
