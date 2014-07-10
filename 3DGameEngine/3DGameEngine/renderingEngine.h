#pragma once

#include "gameObject.h"
#include "Camera.h"
#include "Input.h"
#include <glm\glm.hpp>

class gameObject;

class renderingEngine
{
public:
	renderingEngine();

	
	void Render(gameObject* object);
	char* getOpenGLVersion();
	void input(const Input& input);

	inline Camera& GetMainCamera() { return m_mainCamera; }
	inline glm::fvec3& GetMainCameraPos() { return m_mainCamera.getPos(); }
	inline glm::fvec3& GetMainCameraForward() { return m_mainCamera.getForward(); }
	//inline void SetMainCamera(const Camera& camera) { m_mainCamera = camera; }

	virtual ~renderingEngine();
protected:
private:
	renderingEngine(const renderingEngine& other):
		m_mainCamera(glm::vec3(0.0f, 0.0f, -10.0f), 70.0f, (float)Window::getWidth() / (float)Window::getHeight(), 0.1f, 1000.0f) {}
	void operator=(const renderingEngine& other) {}

	Camera m_mainCamera;
};

