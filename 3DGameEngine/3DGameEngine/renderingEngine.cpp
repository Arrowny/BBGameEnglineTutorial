#include "renderingEngine.h"
#include "Shader.h"
#include "Input.h"
#include "forwardAmbient.h"
#include "baseLight.h"
#include "forwardDirectional.h"

#include <GL/glew.h>

renderingEngine::renderingEngine():
m_mainCamera(glm::vec3(0.0f, 0.0f, -10.0f), 70.0f, (float)Window::getWidth() / (float)Window::getHeight(), 0.1f, 1000.0f),
m_ambientLight(0.2f, 0.2f, 0.2f),
m_directionalLight(baseLight(glm::fvec3(1.0f, 0.0f, 0.0f), 0.2f), glm::fvec3(0.5f, 0.0f, -0.5f)),
m_directionalLight2(baseLight(glm::fvec3(0.0f, 0.0f, 1.0f), 0.2f), glm::fvec3(0.0f, 0.0f, -0.5f))
{
	std::cout << getOpenGLVersion() << std::endl;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_CLAMP);

	glEnable(GL_TEXTURE_2D);
}

renderingEngine::~renderingEngine()
{
	//dtor
}

void renderingEngine::input(const Input& input, float delta)
{
	m_mainCamera.input(input, delta);
}

void renderingEngine::Render(gameObject* object)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	object->render(ForwardAmbient::GetInstance(), this);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);

	object->render(ForwardDirectional::GetInstance(), this);

	directionalLight temp = m_directionalLight;
	m_directionalLight = m_directionalLight2;
	m_directionalLight2 = temp;

	object->render(ForwardDirectional::GetInstance(), this);

    temp = m_directionalLight;
	m_directionalLight = m_directionalLight2;
	m_directionalLight2 = temp;

	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

char* renderingEngine::getOpenGLVersion(){

	return (char*)glGetString(GL_VERSION);

}