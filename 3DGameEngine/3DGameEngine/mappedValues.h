#pragma once

#include <glm/glm.hpp>
#include <map>
#include <string>

class MappedValues
{
public:
	inline void AddVector3f(const std::string& name, glm::fvec3 value) { m_vector3fMap.insert(std::pair<std::string, glm::fvec3>(name, value)); }
	inline void AddFloat(const std::string& name, float value) { m_floatMap.insert(std::pair<std::string, float>(name, value)); }

	inline glm::fvec3 GetVector3f(const std::string& name) const
	{
		std::map<std::string, glm::fvec3>::const_iterator it = m_vector3fMap.find(name);
		if (it != m_vector3fMap.end())
			return it->second;

		return glm::fvec3(0, 0, 0);
	}

	inline float GetFloat(const std::string& name) const
	{
		std::map<std::string, float>::const_iterator it = m_floatMap.find(name);
		if (it != m_floatMap.end())
			return it->second;

		return 0;
	}
protected:
private:
	std::map<std::string, glm::fvec3> m_vector3fMap;
	std::map<std::string, float> m_floatMap;
};