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
	//inline DirectionalLight GetDirectionalLight() { return activeDirectionalLight; }
	//inline PointLight GetPointLight() { return activePointLight; }
	//inline SpotLight GetSpotLight() { return activeSpotLight; }

	void AddLight(BaseLight* lights);
	BaseLight* GetActiveLight();

	void AddCamera(Camera camera);

	~RenderingEngine();
private:

	RenderingEngine(const RenderingEngine& other) :
		mainCamera( 70.0f, (float)WindowParameter::width / (float)WindowParameter::height, 1.0f, 1000.0f) {}
	void operator=(const RenderingEngine& other) {}

	Camera mainCamera;

	glm::fvec3 ambientLight = glm::fvec3(0.1f, 0.1f, 0.1f);
	BaseLight* activeLight;

	std::vector<BaseLight*> lights;
	void ClearLightList();
};


#endif
