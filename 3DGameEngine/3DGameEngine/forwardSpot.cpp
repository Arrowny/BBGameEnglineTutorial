#include "forwardSpot.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

ForwardSpot::ForwardSpot() : Shader("./res/forwardSpot")
{
	/*AddVertexShaderFromFile("./res/forwardSpot.vs");
	AddFragmentShaderFromFile("./res/forwardSpot.fs");

	SetAttribLocation("position", 0);
	SetAttribLocation("texCoord", 1);
	SetAttribLocation("normal", 2);

	CompileShader();

	AddUniform("transform");
	AddUniform("Normal");
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	AddUniform("eyePos");
	AddUniform("spotLight.pointLight.base.color");
	AddUniform("spotLight.pointLight.base.intensity");
	AddUniform("spotLight.pointLight.atten.constant");
	AddUniform("spotLight.pointLight.atten.linear");
	AddUniform("spotLight.pointLight.atten.exponent");
	AddUniform("spotLight.pointLight.position");
	AddUniform("spotLight.pointLight.range");
	AddUniform("spotLight.direction");
	AddUniform("spotLight.cutoff");*/
}

void ForwardSpot::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;
	material.GetTexture("diffuse")->Bind(0);

	SetUniform("Normal", worldMatrix);
	SetUniform("transform", projectedMatrix);

	SetUniform("eyePos", renderingEngine->GetMainCamera().GetTransform().GetTransformedPos());
	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));

	spotLight sLight = *(spotLight*)renderingEngine->GetActiveLight();

	SetUniform("spotLight.pointLight.base.color", sLight.m_color);
	SetUniformf("spotLight.pointLight.base.intensity", sLight.m_intensity);
	SetUniformf("spotLight.pointLight.atten.constant", sLight.atten.m_constant);
	SetUniformf("spotLight.pointLight.atten.linear", sLight.atten.m_linear);
	SetUniformf("spotLight.pointLight.atten.exponent", sLight.atten.m_exponent);
	SetUniform("spotLight.pointLight.position", sLight.GetTransform().GetTransformedPos());
	SetUniformf("spotLight.pointLight.range", sLight.range);
	SetUniform("spotLight.direction", sLight.GetTransform().GetTransformedForward());
	SetUniformf("spotLight.cutoff", sLight.cutoff);
}

