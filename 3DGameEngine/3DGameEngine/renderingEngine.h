#pragma once

#include "Camera.h"
#include "Input.h"
#include "directionalLight.h"
#include "pointLight.h"
#include "spotLight.h"
#include <glm\glm.hpp>
#include <vector>

class gameObject;

class renderingEngine
{
public:
	renderingEngine();

	void Render(gameObject* object);
	char* getOpenGLVersion();
	void input(const Input& input, float delta);

	inline Camera& GetMainCamera() { return m_mainCamera; }
	inline glm::fvec3& GetMainCameraPos() { return m_mainCamera.getPos(); }
	inline glm::fvec3& GetMainCameraForward() { return m_mainCamera.getForward(); }
	inline glm::fvec3& GetAmbientLight() { return m_ambientLight; }
	inline directionalLight& GetDirectionalLight() { return m_activeDirectionalLight; }
	inline pointLight& GetPointLight() { return m_activePointLight; }
	inline spotLight& GetSpotLight() { return m_spotLight; }
	//inline void SetMainCamera(const Camera& camera) { m_mainCamera = camera; }

	inline void AddDirectionalLight(directionalLight* directionalLight) { m_directionalLights.push_back(directionalLight); }
	inline void AddPointLight(pointLight* pointLight) { m_pointLights.push_back(pointLight); }

	virtual ~renderingEngine();
protected:
private:
	renderingEngine(const renderingEngine& other):
		m_mainCamera(glm::vec3(0.0f, 0.0f, -10.0f), 70.0f, (float)Window::getWidth() / (float)Window::getHeight(), 0.1f, 1000.0f) {}
	void operator=(const renderingEngine& other) {}

	Camera m_mainCamera;
	glm::fvec3 m_ambientLight;
	directionalLight m_directionalLight;
	directionalLight m_directionalLight2;
	pointLight m_pointLight;
	pointLight m_pointLight2;
	spotLight m_spotLight;

	directionalLight m_activeDirectionalLight;
	pointLight m_activePointLight;
	std::vector<directionalLight*> m_directionalLights;
	std::vector<pointLight*> m_pointLights;

};

