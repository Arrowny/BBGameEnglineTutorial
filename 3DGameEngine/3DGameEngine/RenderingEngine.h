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

	//inline void SetAmbient(glm::fvec3 ambient) { ambientLight = ambient; }
	//inline void SetDirectionalLight(DirectionalLight directionallight) { directionalLight = directionallight; }

	//void AddDirectionalLight(DirectionalLight directionalLight);
	//void AddPointLight(PointLight pointLight);
	//void AddSpotLight(SpotLight spotLight);

	void AddLight(BaseLight* lights);
	BaseLight* GetActiveLight();


	~RenderingEngine();
private:

	RenderingEngine(const RenderingEngine& other) :
		mainCamera(glm::vec3(0, 1, 0), 70.0f, (float)WindowParameter::width / (float)WindowParameter::height, 1.0f, 1000.0f) {}
	void operator=(const RenderingEngine& other) {}

	Camera mainCamera;

	glm::fvec3 ambientLight = glm::fvec3(0.1f, 0.1f, 0.1f);
	BaseLight* activeLight;

	//DirectionalLight activeDirectionalLight;// = DirectionalLight(BaseLight(glm::vec3(1, 0, 0), 0.2f), glm::vec3(1, 1, 1));
	//DirectionalLight directionalLight2;// = DirectionalLight(BaseLight(glm::vec3(1, 0.5, 0), 0.4f), glm::vec3(-1, 1, -1));
	//PointLight activePointLight;// = PointLight(BaseLight(glm::vec3(0, 0, 1), 0.8f), Attenuation(0.0, 0.0, 0.1), glm::vec3(0, 0, 7), 100);
	//SpotLight activeSpotLight;

	//std::vector<DirectionalLight> directionalLights;
	//std::vector<PointLight> pointLights;
	//std::vector<SpotLight> spotLights;

	std::vector<BaseLight*> lights;
	void ClearLightList();
};


#endif
