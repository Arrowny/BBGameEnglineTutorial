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

	inline Camera& GetMainCamera() { return *m_mainCamera; }
	/*inline glm::fvec3& GetMainCameraPos() { return m_mainCamera->getPos(); }
	inline glm::fvec3& GetMainCameraForward() { return m_mainCamera->getForward(); }*/
	inline glm::fvec3& GetAmbientLight() { return m_ambientLight; }
	inline baseLight* GetActiveLight() { return m_activeLight; }
	//inline void SetMainCamera(const Camera& camera) { m_mainCamera = camera; }

	inline void AddLight(baseLight* light) { m_lights.push_back(light); }
	inline void AddCamera(Camera* camera) { m_mainCamera = camera; }

	virtual ~renderingEngine();
protected:
private:
	renderingEngine(const renderingEngine& other){}
	void operator=(const renderingEngine& other) {}

	Camera* m_mainCamera;
	glm::fvec3 m_ambientLight;

	baseLight* m_activeLight;
	std::vector<baseLight*> m_lights;

};

