#include "forwardAmbient.h"
#include "renderingEngine.h"


ForwardAmbient::ForwardAmbient(const std::string& fileName, glm::vec3 ambientLight) :
Shader(fileName),
m_ambientIntensity(ambientLight)
{

	addUniform("MVP");
	addUniform("ambientIntensity");
}


ForwardAmbient::~ForwardAmbient()
{
}

void ForwardAmbient::updateBasicUniformsAndTexture(const glm::mat4& worldMatrix, Material& mat, RenderingEngine* renderingEngine)
{
	setUniform("MVP", renderingEngine->getCamera()->getProjectionTransform()*worldMatrix);
	setUniform("ambientIntensity", m_ambientIntensity);
}
