#include "textureResource.h"


TextureResource::TextureResource()
{
}


TextureResource::~TextureResource()
{
	glDeleteTextures(1, &m_texture);
}

GLuint* TextureResource::getTexture()
{
	return &m_texture;
}
