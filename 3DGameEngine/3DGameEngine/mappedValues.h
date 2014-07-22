#pragma once
#include <unordered_map>
#include <string>
#include <glm\glm.hpp>

class MappedValues
{
public:
	MappedValues();
	virtual ~MappedValues();

	void addVector(std::string name, glm::vec3 vector) { vecMap[name] = vector; }
	void addFloat(std::string name, float Float) { floatMap[name] = Float; }
	glm::vec3 getVector(std::string name);
	float getFloat(std::string name);

protected:
	std::unordered_map<std::string, glm::vec3> vecMap;
	std::unordered_map<std::string, float> floatMap;
};

