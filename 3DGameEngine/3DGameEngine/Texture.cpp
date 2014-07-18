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

	std::map<std::string, TextureData*>::const_iterator it = s_resourceMap.find(fileName);
	if (it != s_resourceMap.end())
	{
		m_textureData = it->second;
		m_textureData->AddReference();
	}
	else
	{
		int width, height, numComponents;
		unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

		if (imageData == NULL)
			std::cerr << "Unable to load texture: " << fileName << std::endl;

		InitTexture(width, height, imageData);
		stbi_image_free(imageData);

		s_resourceMap.insert(std::pair<std::string, TextureData*>(fileName, m_textureData));
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

void Texture::InitTexture(int width, int height, unsigned char* data)
{
	if (width > 0 && height > 0 && data != 0)
	{
		m_textureData = new TextureData(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_textureData->GetTextureID());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
}


void Texture::Bind(unsigned int unit) const
{
	if (s_lastBind != m_textureData)
	{
		assert(unit >= 0 && unit <= 31);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(m_textureData->GetTextureTarget(), m_textureData->GetTextureID());
		s_lastBind = m_textureData;
	}
}



