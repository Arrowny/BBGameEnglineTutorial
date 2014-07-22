#pragma once

#include <unordered_map>
#include <string>
#include "mappedValues.h"
#include "texture.h"

class Material : public MappedValues
{
public:
	Material(const float& specularIntensity = 1, const float& specularPower = 32);
	Material(const std::string& fileName, const std::string& varName, const float& specularIntensity = 1, const float& specularPower = 32);
	virtual ~Material();

	void addTexture(std::string name, std::string fileName) { textureMap[name] = new Texture(fileName); }

	Texture* getTexture(std::string name);

private:
	std::unordered_map<std::string, Texture*> textureMap;

};

