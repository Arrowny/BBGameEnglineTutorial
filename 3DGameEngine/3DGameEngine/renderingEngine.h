#pragma once

#include "Camera.h"
#include "Input.h"
#include "directionalLight.h"
#include "pointLight.h"
#include "spotLight.h"
#include <glm\glm.hpp>
#include <vector>
#include <map>
#include "mappedValues.h"
#include "Material.h"

class gameObject;

class renderingEngine : public MappedValues
{
public:
	renderingEngine();

	void Render(gameObject* object);
	char* getOpenGLVersion();

	inline Camera& GetMainCamera() { return *m_mainCamera; }
	inline baseLight* GetActiveLight() { return m_activeLight; }
	inline unsigned int GetSamplerSlot(const std::string& samplerName) { return m_samplerMap[samplerName]; }

	inline void AddLight(baseLight* light) { m_lights.push_back(light); }
	inline void AddCamera(Camera* camera) { m_mainCamera = camera; }

	virtual void UpdateUniformStruct(const Transform& transform, const Material& material, Shader* shader, const std::string& uniformName, const std::string& uniformType)
	{
		throw uniformType + " is not supported by the rendering engine";
	}

	virtual ~renderingEngine();
protected:
private:
	renderingEngine(const renderingEngine& other){}
	void operator=(const renderingEngine& other) {}

	Camera* m_mainCamera;
	Shader* m_defaultShader;

	baseLight* m_activeLight;
	std::vector<baseLight*> m_lights;
	std::map<std::string, unsigned int> m_samplerMap;
};

