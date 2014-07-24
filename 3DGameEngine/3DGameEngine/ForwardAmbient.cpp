#include "ForwardAmbient.h"


ForwardAmbient::ForwardAmbient() : Shader("./res/shader/forwardAmbient")
{
}


ForwardAmbient::~ForwardAmbient()
{

}



void ForwardAmbient::Update(Transform& transform, RenderingEngine& renderingEngine, Material& material)
{
	material.GetTexture("diffuse")->Bind(0);
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine.GetMainCamera().GetViewProjection()* worldMatrix;


	SetUniform("T_MVP", projectedMatrix);
	SetUniform("R_ambientIntensity", renderingEngine.GetAmbientLight());

}