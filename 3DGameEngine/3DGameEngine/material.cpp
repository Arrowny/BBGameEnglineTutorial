#include "material.h"


Material::Material(const float& specularIntensity, const float& specularPower)
{
	floatMap["specularIntensity"] = specularIntensity;
	floatMap["specularPower"] = specularPower;
}

Material::Material(const std::string& fileName, const std::string& varName, const float& specularIntensity, const float& specularPower)
{
	textureMap[varName] = new Texture("./res/texture_files/" + fileName);
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
