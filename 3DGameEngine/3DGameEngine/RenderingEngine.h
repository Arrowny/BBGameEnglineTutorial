#ifndef _RENDERINGENGINE_H
#define _RENDERINGENGINE_H
#pragma once

#include <GL/glew.h>
#include <glm\glm.hpp>
#include <vector>
#include "Camera.h"
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

	~RenderingEngine();
private:

	RenderingEngine(const RenderingEngine& other) :
		mainCamera(glm::vec3(0, 1, -4), 70.0f, (float)WindowParameter::width / (float)WindowParameter::height, 1.0f, 1000.0f) {}
	void operator=(const RenderingEngine& other) {}

	Camera mainCamera;
	//Camera m_camera;

};


#endif
