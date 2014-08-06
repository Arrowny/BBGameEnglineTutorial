#include "physicsComponents.h"

PhysicsComponents::PhysicsComponents() :
m_vec3fMap(std::unordered_map<std::string, glm::fvec3>()),
m_floatMap(std::unordered_map<std::string, float>()),
m_intMap(std::unordered_map<std::string, int>())
{
	SetInt("numEmit", 1);
}

PhysicsComponents::PhysicsComponents(const int& numEmittedParticles)
{
	SetInt("numEmit", numEmittedParticles);
}

PhysicsComponents::~PhysicsComponents()
{
}

glm::fvec3 PhysicsComponents::GetVector3f(const std::string& name) const
{
	std::unordered_map<std::string, glm::fvec3>::const_iterator it = m_vec3fMap.find(name);
	if (it != m_vec3fMap.end())
		return it->second;

	return glm::fvec3(0.0, 0.0, 0.0);
}

float PhysicsComponents::GetFloat(const std::string& name) const
{
	std::unordered_map<std::string, float>::const_iterator it = m_floatMap.find(name);
	if (it != m_floatMap.end())
		return it->second;

	return 0.0;
}

int PhysicsComponents::GetInt(const std::string& name) const
{
	std::unordered_map<std::string, int>::const_iterator it = m_intMap.find(name);
	if (it != m_intMap.end())
		return it->second;

	return 0;
}
