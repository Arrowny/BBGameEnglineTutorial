#include "renderingEngine.h"
#include "forwardAmbient.h"
#include "forwardDirectional.h"
#include "forwardPoint.h"
#include "forwardSpot.h"
#include "gameObject.h"
#include <GL/glew.h>

renderingEngine::renderingEngine():
//m_mainCamera(glm::vec3(0.0f, 0.0f, -10.0f), 70.0f, (float)Window::getWidth() / (float)Window::getHeight(), 0.1f, 1000.0f),
m_ambientLight(0.2f, 0.2f, 0.2f)
//m_activeLight(glm::fvec3(1.0f, 0.0f, 0.0f), 0.2f)
//m_activeDirectionalLight(baseLight(glm::fvec3(1.0f, 0.0f, 0.0f), 0.2f), glm::fvec3(0.5f, 0.0f, -0.5f)),
//m_activePointLight(baseLight(glm::fvec3(0.0f, 1.0f, 0.0f), 0.4f), Attenuation(0, 0, 1), glm::fvec3(0.0f, 1.0f, -0.5f), 10)
//m_spotLight(pointLight(baseLight(glm::fvec3(1, 1, 0), 0.8f), Attenuation(0, 0, 0.5f), glm::fvec3(-0.5, -0.8, -0.5), 30), glm::normalize(glm::fvec3(0, 1, 0)), 0.8f)
{
	std::cout << getOpenGLVersion() << std::endl;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_CLAMP);

	glEnable(GL_TEXTURE_2D);

	m_activeLight = new baseLight();
	m_mainCamera = new Camera(70.0f, Window::getAspect(), 0.1f, 1000.0f);
}

renderingEngine::~renderingEngine()
{
	//dtor
}

void renderingEngine::input(const Input& input, float delta)
{
	m_mainCamera->input(input, delta);
}

void renderingEngine::Render(gameObject* object)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_lights.clear();

	object->AddToRenderingEngine(this);

	object->render(ForwardAmbient::GetInstance(), this);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);

	for (unsigned int i = 0; i < m_lights.size(); i++)
	{
		m_activeLight = m_lights[i];
		object->render(m_activeLight->GetShader(), this);
	}

	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);
}

char* renderingEngine::getOpenGLVersion(){

	return (char*)glGetString(GL_VERSION);

}