#include "renderingEngine.h"
#include "forwardAmbient.h"
#include "forwardDirectional.h"
#include "forwardPoint.h"
#include "forwardSpot.h"
#include "gameObject.h"
#include <GL/glew.h>

renderingEngine::renderingEngine()
{
	std::cout << getOpenGLVersion() << std::endl;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_CLAMP);

	glEnable(GL_TEXTURE_2D);

	m_activeLight = new baseLight();
	m_mainCamera = new Camera(70.0f, Window::getAspect(), 0.1f, 1000.0f);

	AddVector3f("ambientLight", glm::fvec3(0.1f, 0.1f, 0.1f));
	m_defaultShader = new Shader("./res/forwardAmbient");

	m_samplerMap.insert(std::pair<std::string, unsigned int>("diffuse", 0));
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

	object->render(m_defaultShader, this);
	
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