#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include "Texture.h"

class Texture3d : public Texture
{
public:
	Texture3d(const std::string& Directory,
		const std::string& PosXFilename,
		const std::string& NegXFilename,
		const std::string& PosYFilename,
		const std::string& NegYFilename,
		const std::string& PosZFilename,
		const std::string& NegZFilename);
	virtual ~Texture3d();

	virtual void Bind(unsigned int unit) const;

private:

	void InitTexture(std::string* fileNames);
	//GLuint m_texture3D;
};

