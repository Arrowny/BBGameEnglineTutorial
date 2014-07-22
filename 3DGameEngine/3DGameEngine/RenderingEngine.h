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

	inline Camera& GetMainCamera() { return *mainCamera; }

	inline glm::fvec3 GetAmbientLight() { return ambientLight; }

	void AddLight(BaseLight* lights);
	BaseLight* GetActiveLight();

	void AddCamera(Camera* camera);

	~RenderingEngine();
private:

	RenderingEngine(const RenderingEngine& other){}
	void operator=(const RenderingEngine& other) {}

	Camera* mainCamera;

	glm::fvec3 ambientLight = glm::fvec3(0.1f, 0.1f, 0.1f);
	BaseLight* activeLight;

	std::vector<BaseLight*> lights;
	void ClearLightList();
};


#endif
