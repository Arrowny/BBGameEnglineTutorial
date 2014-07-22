#pragma once
#include <string>
#include <vector>
#include <glm\glm.hpp>
#include <GL\glew.h>
#include "timing.h"
#include "Lights.h"
#include "mappedValues.h"

class GameObject;
class Shader;
class Camera;

class RenderingEngine : public MappedValues
{
public:
	RenderingEngine();
	virtual ~RenderingEngine();

	void RenderGameObject(GameObject* gameObject);
	void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
	std::string getOpenGLVersion();
	Camera* getCamera() { return m_camera; }
	int getSamplerSlot(std::string samplerName);
	void addLight(BaseLight* baseLight) { m_lights.push_back(baseLight); }
	void addCamera(Camera* camera) { m_camera = camera; }

	BaseLight* activeLight;
private:
	RenderingEngine(const RenderingEngine& other) {}
	void operator=(const RenderingEngine& other) {}

	Camera* m_camera;
	std::vector<BaseLight*> m_lights;
	Shader* m_ambientShader;
	std::unordered_map<std::string, int> m_samplerMap;
};

