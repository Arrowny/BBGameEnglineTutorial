#include "material.h"


Material::Material(const float& specularIntensity, const float& specularPower)
{
	floatMap["specularIntensity"] = specularIntensity;
	floatMap["specularPower"] = specularPower;
}

Material::Material(const std::string& fileName, const float& specularIntensity, const float& specularPower)
{
	textureMap[fileName] = new Texture("./res/texture_files/" + fileName);
	floatMap["specularIntensity"] = specularIntensity;
	floatMap["specularPower"] = specularPower;
}

Material::~Material()
{
}

Texture* Material::getTexture(std::string name)
{
	Texture* result = textureMap[name];
	if (result != NULL)
		return result;

	return new Texture("./res/texture_files/bricks.jpg"); //default texture. Replace this with some more sensible default.
}

glm::vec3 Material::getVector(std::string name)
{
	glm::vec3 result = vecMap[name];
	if (result != glm::vec3(0.0,0.0,0.0))
		return result;

	return glm::vec3(0.0, 0.0, 0.0);
}

float Material::getFloat(std::string name)
{
	float result = floatMap[name];
	if (result != 0.0)
		return result;

	return 0.0;
}
