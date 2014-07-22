#include "texture.h"
#include <iostream>
#include <cassert>
#include "util.h"


Texture::Texture(const std::string& fileName)
{
	this->m_texFileName = fileName;

	if (texResourceMap.find(m_texFileName) == texResourceMap.end()) //only set up new texture if texture has not been created.
	{
		int width, height, numComponents;
		unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

		if (imageData == NULL)
		{
			std::cerr << "Error: Texture loading error for file " + fileName << std::endl;
		}

		m_texResource = new TextureResource();
		initTexture(imageData, width, height);
	}
	else
	{
		texResourceCount[m_texFileName]++;
	}
}

void Texture::initTexture(unsigned char* imageData, int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, *m_texResource->getTexture());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
	texResourceMap[m_texFileName] = m_texResource;
}

Texture::~Texture()
{
	if (texResourceMap[m_texFileName] == 0)
	{
		meshResourceMap.erase(m_texFileName);
	}
	else 
	{
		texResourceCount[m_texFileName]--;
	}
}

void Texture::Bind(const unsigned int& samplerSlot)
{
	assert(samplerSlot >= 0 && samplerSlot <= 31);
	glActiveTexture(GL_TEXTURE0 + samplerSlot);
	glBindTexture(GL_TEXTURE_2D, *texResourceMap[m_texFileName]->getTexture());
}
