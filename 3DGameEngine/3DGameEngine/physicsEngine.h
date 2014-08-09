#pragma once
#include "mappedValues.h"
#include "Material.h"

class GameObject;
class Shader;

class PhysicsEngine : public MappedValues
{
public:
	PhysicsEngine(const float& delta);
	virtual ~PhysicsEngine();

	void UpdatePhysics(GameObject* object);

	virtual void UpdateUniformStruct(Shader* shader, const std::string& uniformName, const std::string& uniformType)
	{
		throw uniformType + " is not supported by the rendering engine";
	}

	inline unsigned int GetSamplerSlot(const std::string& samplerName) { return m_samplerMap[samplerName]; }

private:
	Shader* m_generalPhysics; //TODO: no general physics implemented yet

	std::map<std::string, unsigned int> m_samplerMap;
};

