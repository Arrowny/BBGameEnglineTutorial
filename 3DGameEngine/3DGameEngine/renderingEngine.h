#pragma once

#include "Camera.h"
#include "Input.h"
#include "Lights.h"
#include <glm\glm.hpp>
#include <vector>
#include <map>
#include "mappedValues.h"
#include "Material.h"

class GameObject;
class SkyBoxRenderer;

class RenderingEngine : public MappedValues
{
public:
	RenderingEngine();

	void Render(GameObject* object);

	inline Camera& GetMainCamera() { return *m_mainCamera; }
	inline BaseLight* GetActiveLight() { return m_activeLight; }
	inline unsigned int GetSamplerSlot(const std::string& samplerName) { return m_samplerMap[samplerName]; }

	inline void AddLight(BaseLight* light) { m_lights.push_back(light); }
	inline void AddCamera(Camera* camera) { m_mainCamera = camera; }
	inline void AddSkyBox(SkyBoxRenderer* skybox) { m_skyBox = skybox; }

	virtual void UpdateUniformStruct(const Transform& transform, const Material& material, Shader* shader, const std::string& uniformName, const std::string& uniformType)
	{
		throw uniformType + " is not supported by the rendering engine";
	}

	virtual ~RenderingEngine();
protected:
private:
	RenderingEngine(const RenderingEngine& other){}
	void operator=(const RenderingEngine& other) {}

	Camera* m_mainCamera;
	SkyBoxRenderer* m_skyBox;
	Shader* m_defaultShader;

	BaseLight* m_activeLight;
	std::vector<BaseLight*> m_lights;
	std::map<std::string, unsigned int> m_samplerMap;
};

