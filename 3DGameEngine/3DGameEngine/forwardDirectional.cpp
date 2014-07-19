#include "forwardDirectional.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

ForwardDirectional::ForwardDirectional() : Shader("./res/forwardDirectional")
{
	/*AddVertexShaderFromFile("./res/forwardDirectional.vs");
	AddFragmentShaderFromFile("./res/forwardDirectional.fs");

	SetAttribLocation("position", 0);
	SetAttribLocation("texCoord", 1);
	SetAttribLocation("normal", 2);
	CompileShader();

	AddUniform("transform");
	AddUniform("Normal");
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	AddUniform("eyePos");
	AddUniform("directionalLight.base.color");
	AddUniform("directionalLight.base.intensity");
	AddUniform("directionalLight.direction");*/
}

void ForwardDirectional::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;
	material.GetTexture("diffuse")->Bind(0);

	SetUniform("Normal", worldMatrix);
	SetUniform("transform", projectedMatrix);

	SetUniform("eyePos", renderingEngine->GetMainCamera().GetTransform().GetTransformedPos());
	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));

	directionalLight dirLight = *(directionalLight*)renderingEngine->GetActiveLight();

	SetUniform("directionalLight.direction", dirLight.GetTransform().GetTransformedForward());
	SetUniform("directionalLight.base.color", dirLight.m_color);
	SetUniformf("directionalLight.base.intensity", dirLight.m_intensity);
}
