#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

class PhysicsComponents
{
public:
	PhysicsComponents();
	PhysicsComponents(const int& numEmittedParticles);
	virtual ~PhysicsComponents();

	inline void SetVector3f(const std::string& name, glm::fvec3 value) { m_vec3fMap[name] = value; }
	inline void SetFloat(const std::string& name, float value) { m_floatMap[name] = value; }
	inline void SetInt(const std::string& name, int value) { m_intMap[name] = value; }

	glm::fvec3 GetVector3f(const std::string& name) const;
	float GetFloat(const std::string& name) const;
	int GetInt(const std::string& name) const;

private:
	std::unordered_map<std::string, glm::fvec3> m_vec3fMap;
	std::unordered_map<std::string, float> m_floatMap;
	std::unordered_map<std::string, int> m_intMap;
};

