#include "Texture.h"
#include "stb_image.h"
#include <iostream>
#include <cassert>


const TextureData* Texture::s_lastBind = 0;
std::map<std::string, TextureData*> Texture::s_resourceMap;

TextureData::TextureData(GLenum textureTarget)
{
	glGenTextures(1, &m_textureID);
	m_textureTarget = textureTarget;
}


TextureData::~TextureData()
{
	if (m_textureID) glDeleteTextures(1, &m_textureID);
}


Texture::Texture(const std::string& fileName)
{
	m_fileName = fileName;
	int width, height, numComponents;
	
	std::map<std::string, TextureData*>::const_iterator it = s_resourceMap.find(fileName);
	if (it != s_resourceMap.end())
	{
		m_textureData = it->second;
		m_textureData->AddReference();
	}
	else
	{
		unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

		if (imageData == NULL)
			std::cerr << "Unable to load texture: " << fileName << std::endl;	

		InitTexture(width, height, imageData, GL_TEXTURE_2D,GL_LINEAR);
		stbi_image_free(imageData);
	}
}

Texture::~Texture()
{
	if (m_textureData && m_textureData->RemoveReference())
	{
		if (m_fileName.length() > 0)
			s_resourceMap.erase(m_fileName);

		delete m_textureData;
	}
}
void Texture::InitTexture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter)
{
	if (width > 0 && height > 0 && data != 0)
	{
		m_textureData = new TextureData(GL_TEXTURE_2D);
		glBindTexture(textureTarget, m_textureData->GetTextureID());

		glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, filter);

		glTexImage2D(textureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
}
void Texture::Bind(unsigned int unit)
{
	if (s_lastBind != m_textureData)
	{
		assert(unit >= 0 && unit <= 31);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(m_textureData->GetTextureTarget(), m_textureData->GetTextureID());
		s_lastBind = m_textureData;
	}
}

