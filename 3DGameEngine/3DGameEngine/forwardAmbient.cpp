#include "forwardAmbient.h"


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

void ForwardAmbient::updateBasicUniformsAndTexture(Camera& camera, const glm::mat4& worldMatrix, const Material& mat)
{
	setUniform("MVP", camera.getProjectionTransform()*worldMatrix);
	setUniform("ambientIntensity", m_ambientIntensity);
}
