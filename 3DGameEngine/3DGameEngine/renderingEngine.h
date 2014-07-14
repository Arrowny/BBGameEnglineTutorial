#pragma once
#include "gameObject.h"
#include <string>
#include <vector>
#include <glm\glm.hpp>
#include <GL\glew.h>
#include "shader.h"
#include "camera.h"
#include "timing.h"

class RenderingEngine
{
public:
	RenderingEngine();
	virtual ~RenderingEngine();

	void RenderGameObject(GameObject* gameObject, std::vector<Shader*> shaders);
	void ProcessInput(Input* &input, double delta) { m_camera->input(*input, delta); }
	void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
	void setTextures(bool enabled);
	std::string getOpenGLVersion();
	
	void setCamera(Camera camera) { m_camera = new Camera(camera); }
	void setCamera(glm::vec3 pos, glm::vec3 lookAtPoint, glm::vec3 up, double zNear, double zFar, double fov, double screenWidth, double screenHeight)
	{
		m_camera = new Camera(pos, lookAtPoint, up, zNear, zFar, fov, screenWidth, screenHeight);
	}
	void updateCameraPerspective(double zNear, double zFar, double fov, double screenWidth, double screenHeight);
	Camera getCamera() { return *m_camera; }

private:
	RenderingEngine(const RenderingEngine& other) {}
	void operator=(const RenderingEngine& other) {}

	Camera* m_camera;
};

