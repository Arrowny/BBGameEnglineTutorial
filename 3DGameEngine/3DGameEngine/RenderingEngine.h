#ifndef _RENDERINGENGINE_H
#define _RENDERINGENGINE_H
#pragma once

#include <GL/glew.h>
#include <glm\glm.hpp>
#include <vector>
#include "Camera.h"
#include "Lights.h"
#include "Material.h"
#include <map>
class GameObject;

class RenderingEngine
{
public:
	RenderingEngine();
	
	void input(Input input, float delta);
	void render(GameObject* object);

	inline Camera& GetMainCamera() { return *mainCamera; }

	void AddLight(BaseLight* lights);
	BaseLight* GetActiveLight();
	void AddCamera(Camera* camera);

	inline unsigned int GetSamplerSlot(const std::string& samplerName) { return m_samplerMap[samplerName]; }
	inline glm::vec3 GetVector(const std::string& name) const
	{
		std::map<std::string, glm::vec3>::const_iterator it = m_vectorMap.find(name);
		if (it != m_vectorMap.end())
			return it->second;

		return glm::vec3(0, 0, 0);
	}


	inline float GetFloat(const std::string& name) const
	{
		std::map<std::string, float>::const_iterator it = m_floatMap.find(name);
		if (it != m_floatMap.end())
			return it->second;

		return 0;
	}
	inline void UpdateUniformStruct(const Transform& transform, const Material& material, Shader* shader, const std::string& uniformName, const std::string& uniformType)
	{
		throw uniformType + " is not supported by the rendering engine";
	}
	~RenderingEngine();
private:

	RenderingEngine(const RenderingEngine& other){}
	void operator=(const RenderingEngine& other) {}

	Camera* mainCamera;

	BaseLight* activeLight;
	std::vector<BaseLight*> lights;
	void ClearLightList();

	Shader* m_shaderAmbient;
	std::map<std::string, unsigned int> m_samplerMap;
	std::map<std::string, glm::vec3> m_vectorMap;
	std::map<std::string, float> m_floatMap;

	inline void AddSampler(const std::string& name, unsigned int value){ m_samplerMap.insert(std::pair<std::string, unsigned int>(name, value)); }
	inline void AddVector(const std::string& name, glm::vec3 value) { m_vectorMap.insert(std::pair<std::string, glm::vec3>(name, value)); }
	inline void AddFloat(const std::string& name, float value) { m_floatMap.insert(std::pair<std::string, float>(name, value)); }
};


#endif
