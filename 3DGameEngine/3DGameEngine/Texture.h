
#include <string>
#include <GL/glew.h>
#include "ReferenceCounter.h"
#include <map>

struct TextureData : public ReferenceCounter
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
	
	Texture(const std::string& fileName);
	void InitTexture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter);
	void Bind(unsigned int unit);

	virtual ~Texture();
protected:
private:

	TextureData* m_textureData;
	std::string m_fileName;

	static std::map<std::string, TextureData*> s_resourceMap;
	static const TextureData* s_lastBind;

	Texture(const Texture& other) {}
	void operator=(const Texture& other) {}



};