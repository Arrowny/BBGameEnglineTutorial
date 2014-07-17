#ifndef _RENDERINGENGINE_H
#define _RENDERINGENGINE_H
#pragma once

#include <GL/glew.h>
#include <glm\glm.hpp>
#include <vector>
#include "Camera.h"
#include "Lights.h"
class GameObject;

class RenderingEngine
{
public:
	RenderingEngine();
	
	void input(Input input, float delta);
	void render(GameObject* object);
	void clearScreen();
	const GLubyte* getOpenGLVersion();

	inline Camera& GetMainCamera() { return mainCamera; }
	inline glm::fvec3& GetMainCameraPos() { return mainCamera.GetPos(); }
	inline glm::fvec3& GetMainCameraForward() { return mainCamera.GetForward(); }

	inline glm::fvec3 GetAmbientLight() { return ambientLight; }
	inline DirectionalLight GetDirectionalLight() { return directionalLight; }
	inline PointLight GetPointLight() { return pointLight; }

	inline void SetAmbient(glm::fvec3 ambient) { ambientLight = ambient; }
	inline void SetDirectionalLight(DirectionalLight directionallight) { directionalLight = directionallight; }
	~RenderingEngine();
private:

	RenderingEngine(const RenderingEngine& other) :
		mainCamera(glm::vec3(0, 1, 0), 70.0f, (float)WindowParameter::width / (float)WindowParameter::height, 1.0f, 1000.0f) {}
	void operator=(const RenderingEngine& other) {}

	Camera mainCamera;
	//Camera m_camera;
	glm::fvec3 ambientLight = glm::fvec3(0.2f, 0.2f, 0.2f);
	DirectionalLight directionalLight;// = DirectionalLight(BaseLight(glm::vec3(1, 0, 0), 0.2f), glm::vec3(1, 1, 1));
	DirectionalLight directionalLight2;// = DirectionalLight(BaseLight(glm::vec3(1, 0.5, 0), 0.4f), glm::vec3(-1, 1, -1));

	PointLight pointLight;// = PointLight(BaseLight(glm::vec3(0, 0, 1), 0.8f), Attenuation(0.0, 0.0, 0.1), glm::vec3(0, 0, 7), 100);
};


#endif
