#include "forwardAmbient.h"
#include "renderingEngine.h"


ForwardAmbient::ForwardAmbient(const std::string& fileName) :
Shader(fileName)
{
}


ForwardAmbient::~ForwardAmbient()
{
}

void ForwardAmbient::updateUniforms(const glm::mat4& worldMatrix, Material& mat, RenderingEngine* renderingEngine)
{
	Shader::updateUniforms(worldMatrix, mat, renderingEngine);
}
