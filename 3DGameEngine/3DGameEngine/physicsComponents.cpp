#include "physicsComponents.h"
#include "texture3D.h"

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

PhysicsComponents::PhysicsComponents(const int& numEmittedParticles, Texture3D* texture)
{
	SetInt("numEmit", numEmittedParticles);
	SetTexture("vectorField", texture);
	SetVector3f("Size", glm::fvec3((float)texture->GetTexWidth(), (float)texture->GetTexHeight(), (float)texture->GetTexDepth()));
	SetVector3f("Extent", glm::vec3(2, 4, 2));

}

PhysicsComponents::~PhysicsComponents()
{
}

Texture* PhysicsComponents::GetTexture(const std::string& name) const
{
	std::unordered_map<std::string, Texture*>::const_iterator it = m_textureMap.find(name);
	if (it != m_textureMap.end())
		return it->second;

	return 0;
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
