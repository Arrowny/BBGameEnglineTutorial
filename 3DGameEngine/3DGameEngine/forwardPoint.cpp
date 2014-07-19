#include "forwardPoint.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

ForwardPoint::ForwardPoint() : Shader("./res/forwardPoint")
{
	/*AddVertexShaderFromFile("./res/forwardPoint.vs");
	AddFragmentShaderFromFile("./res/forwardPoint.fs");

	SetAttribLocation("position", 0);
	SetAttribLocation("texCoord", 1);
	SetAttribLocation("normal", 2);

	CompileShader();

	AddUniform("transform");
	AddUniform("Normal");
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	AddUniform("eyePos");
	AddUniform("pointLight.base.color");
	AddUniform("pointLight.base.intensity");
	AddUniform("pointLight.atten.constant");
	AddUniform("pointLight.atten.linear");
	AddUniform("pointLight.atten.exponent");
	AddUniform("pointLight.position");
	AddUniform("pointLight.range");*/
}

void ForwardPoint::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;
	material.GetTexture("diffuse")->Bind(0);

	SetUniform("Normal", worldMatrix);
	SetUniform("transform", projectedMatrix);

	SetUniform("eyePos", renderingEngine->GetMainCamera().GetTransform().GetTransformedPos());
	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));

	pointLight pLight = *(pointLight*)renderingEngine->GetActiveLight();

	SetUniform("pointLight.base.color", pLight.m_color);
	SetUniformf("pointLight.base.intensity", pLight.m_intensity);
	SetUniformf("pointLight.atten.constant", pLight.atten.m_constant);
	SetUniformf("pointLight.atten.linear", pLight.atten.m_linear);
	SetUniformf("pointLight.atten.exponent", pLight.atten.m_exponent);
	SetUniform("pointLight.position", pLight.GetTransform().GetTransformedPos());
	SetUniformf("pointLight.range", pLight.range);
}