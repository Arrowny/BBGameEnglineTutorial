#pragma once
#include <string>
#include <vector>
#include <glm\glm.hpp>
#include <GL\glew.h>
#include "timing.h"
#include "Lights.h"

class GameObject;
class Shader;
class Camera;

class RenderingEngine
{
public:
	RenderingEngine();
	virtual ~RenderingEngine();

	void RenderGameObject(GameObject* gameObject);
	void ProcessInput(Input* &input, double delta, GameObject* gameObject);
	void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
	void setTextures(bool enabled);
	std::string getOpenGLVersion();
	
	//void setCamera(Camera camera) { m_camera = new Camera(camera); }
	//void setCamera(glm::vec3 pos, glm::vec3 lookAtPoint, glm::vec3 up, double zNear, double zFar, double fov, double screenWidth, double screenHeight)
	//{
	//	m_camera = new Camera(pos, lookAtPoint, up, zNear, zFar, fov, screenWidth, screenHeight);
	//}
	//void updateCameraPerspective(double zNear, double zFar, double fov, double screenWidth, double screenHeight);

	Camera* getCamera() { return m_camera; }


	void addLight(BaseLight* baseLight) { m_lights.push_back(baseLight); }
	void addCamera(Camera* camera) { m_camera = camera; }

	BaseLight* activeLight;
private:
	RenderingEngine(const RenderingEngine& other) {}
	void operator=(const RenderingEngine& other) {}

	Camera* m_camera;
	std::vector<BaseLight*> m_lights;
	Shader* m_ambientShader;
};

