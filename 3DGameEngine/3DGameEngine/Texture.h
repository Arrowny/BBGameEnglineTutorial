#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>
#include "referenceCounter.h"
#include <map>

class TextureData : public ReferenceCounter
{
public:
	TextureData(GLenum textureTarget);
	virtual ~TextureData();

	inline GLenum GetTextureTarget() { return m_textureTarget; }
	inline GLuint GetTextureID() { return m_textureID; }
protected:
private:
	TextureData(TextureData& other) {}
	void operator=(TextureData& other) {}

	GLenum m_textureTarget = GL_TEXTURE_2D;
	GLuint m_textureID = GL_LINEAR;
};

class Texture
{
public:
	Texture();
	Texture(const std::string& fileName);

	virtual void Bind(unsigned int unit) const;

	virtual ~Texture();
protected:
	GLuint m_texture;

private:
	static std::map<std::string, TextureData*> textureResourceMap;
	static const TextureData* s_lastBind;

	Texture(const Texture& other) {}
	void operator=(const Texture& other) {}

	TextureData* m_textureData;
	std::string m_fileName;

	void InitTexture(int width, int height, unsigned char* data);

};

#endif