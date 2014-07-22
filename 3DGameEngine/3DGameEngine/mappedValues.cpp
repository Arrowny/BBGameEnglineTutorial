#include "mappedValues.h"


MappedValues::MappedValues()
{
}


MappedValues::~MappedValues()
{
}

glm::vec3 MappedValues::getVector(std::string name)
{
	glm::vec3 result = vecMap[name];
	if (result != glm::vec3(0.0, 0.0, 0.0))
		return result;

	return glm::vec3(0.0, 0.0, 0.0);
}

float MappedValues::getFloat(std::string name)
{
	float result = floatMap[name];
	if (result != 0.0)
		return result;

	return 0.0;
}
