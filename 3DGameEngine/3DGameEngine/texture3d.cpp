#include "texture3d.h"
#include <iostream>
#include <cassert>
#include "stb_image.h"
#define NUMBER_OF_TEXTURE_FACES 6

static const GLenum types[6] = 
		{	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

Texture3d::Texture3d(
	const std::string& PosXFilename,
	const std::string& NegXFilename,
	const std::string& PosYFilename,
	const std::string& NegYFilename,
	const std::string& PosZFilename,
	const std::string& NegZFilename)
{
	std::string BaseDir = "./res/skybox/";
	std::string fileNames[6];
	//std::string BaseDir = (Directory[Directory.size() - 2] == '/') ? Directory : Directory + "/";

	fileNames[0] = BaseDir + PosXFilename;
	fileNames[1] = BaseDir + NegXFilename;
	fileNames[2] = BaseDir + PosYFilename;
	fileNames[3] = BaseDir + NegYFilename;
	fileNames[4] = BaseDir + PosZFilename;
	fileNames[5] = BaseDir + NegZFilename;

	InitTexture(fileNames);
}

Texture3d::~Texture3d()
{
	glDeleteTextures(1, &m_texture);
}

void Texture3d::InitTexture(std::string* fileNames)
{
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

	for (int ii = 0; ii < NUMBER_OF_TEXTURE_FACES; ii++)
	{
		int width, height, numComponents;
		unsigned char* imageData = stbi_load((fileNames[ii]).c_str(), &width, &height, &numComponents, 4);

		if (imageData == NULL)
		{
			std::cerr << "Unable to load texture: " << fileNames[ii] << std::endl;
			exit(1);
		}

		glTexImage2D(types[ii], 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		stbi_image_free(imageData);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

void Texture3d::Bind(unsigned int unit) const
{
	assert(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
}