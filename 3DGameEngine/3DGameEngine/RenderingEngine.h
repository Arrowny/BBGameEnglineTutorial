#pragma once
#include "GameObject.h"
//#include "BasicShader.h"

class RenderingEngine
{
public:
	RenderingEngine();
	

	void render(GameObject* object);
	void clearScreen();
	const GLubyte* getOpenGLVersion();

	inline Camera& GetMainCamera() { return m_mainCamera; }
	inline glm::fvec3& GetMainCameraPos() { return m_mainCamera.GetPos(); }
	inline glm::fvec3& GetMainCameraForward() { return m_mainCamera.GetForward(); }

	~RenderingEngine();
private:

	RenderingEngine(const RenderingEngine& other) :
		m_mainCamera(glm::vec3(0, 1, -4), 70.0f, (float)WindowParameter::width / (float)WindowParameter::height, 1.0f, 1000.0f) {}
	void operator=(const RenderingEngine& other) {}

	Camera m_mainCamera;
	//Camera m_camera;

};

