#pragma once

#include <map>
#include <string>
#include <glm\glm.hpp>
#include "texture.h"

class Material
{
public:
	Material(const float& specularIntensity = 1, const float& specularPower = 32);
	Material(const std::string& fileName, const float& specularIntensity = 1, const float& specularPower = 32);
	virtual ~Material();

	void addTexture(std::string name, std::string fileName) { textureMap[name] = new Texture(fileName); }
	void addVector(std::string name, glm::vec3 vector) { vecMap[name] = vector; }
	void addFloat(std::string name, float Float) { floatMap[name] = Float; }

	Texture* getTexture(std::string name);
	glm::vec3 getVector(std::string name);
	float getFloat(std::string name);

private:
	std::map<std::string, Texture*> textureMap;
	std::map<std::string, glm::vec3> vecMap;
	std::map<std::string, float> floatMap;
};

