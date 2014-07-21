#pragma once
#include <GL\glew.h>

class TextureResource
{
public:
	TextureResource();
	virtual ~TextureResource();

	GLuint* getTexture();

private:
	GLuint m_texture;
};

