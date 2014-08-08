#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include "Texture.h"

class TextureCube : public Texture
{
public:
	TextureCube(
		const std::string& PosXFilename,
		const std::string& NegXFilename,
		const std::string& PosYFilename,
		const std::string& NegYFilename,
		const std::string& PosZFilename,
		const std::string& NegZFilename);
	virtual ~TextureCube();

	virtual void Bind(unsigned int unit) const;

private:

	void InitTexture(std::string* fileNames);
};

