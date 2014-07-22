#include "forwardDirectional.h"


ForwardDirectional::ForwardDirectional(std::string fileName) :
Shader(fileName)
{

}


ForwardDirectional::~ForwardDirectional()
{
}


void ForwardDirectional::updateUniforms(const glm::mat4& worldMatrix, Material& mat, RenderingEngine* renderingEngine)
{
	Shader::updateUniforms(worldMatrix, mat, renderingEngine);
}
