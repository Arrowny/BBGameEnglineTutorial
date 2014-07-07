#pragma once

#include <string>
#include <GL\glew.h>
#include "stb_image.h"

class Texture
{
public:
	Texture(const std::string& fileName);
	virtual ~Texture();

	void Bind(const unsigned int& whichText);

private:
	Texture(const Texture& other) {}
	void operator=(const Texture& other) {}

	GLuint m_texture;
};

