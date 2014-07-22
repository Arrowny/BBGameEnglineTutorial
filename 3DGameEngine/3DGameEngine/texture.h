#pragma once

#include <string>
#include <GL\glew.h>
#include "stb_image.h"
#include "textureResource.h"

class Texture
{
public:
	Texture(const std::string& fileName);
	virtual ~Texture();

	void Bind(const unsigned int& whichText);
	std::string getTextureFileName() { return m_texFileName; }

private:
	Texture(const Texture& other) {}
	void operator=(const Texture& other) {}


	void initTexture(unsigned char* imageData, int width, int height);

	std::string m_texFileName;
	TextureResource* m_texResource;
	//GLuint m_texture;
};

