#include "forwardAmbient.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

ForwardAmbient::ForwardAmbient() :
Shader("./res/forwardAmbient")
{
	/*AddVertexShaderFromFile("./res/forwardAmbient.vs");
	AddFragmentShaderFromFile("./res/forwardAmbient.fs");

	SetAttribLocation("position", 0);
	SetAttribLocation("texCoord", 1);
	CompileShader();

	AddUniform("transform");
	AddUniform("ambientLight");*/
}

void ForwardAmbient::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{
	material.GetTexture("diffuse")->Bind(0);

	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;

	SetUniform("transform", projectedMatrix);
	SetUniform("ambientLight", renderingEngine->GetAmbientLight());
}