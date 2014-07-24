#include "ForwardDirectional.h"


ForwardDirectional::ForwardDirectional() :Shader("./res/shader/fowardDirectional")
{

}


ForwardDirectional::~ForwardDirectional()
{

}



void ForwardDirectional::Update(Transform& transform, RenderingEngine& renderingEngine, Material& material)
{
	material.GetTexture("diffuse")->Bind(0);

	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine.GetMainCamera().GetViewProjection()* worldMatrix;

	SetUniform("T_model",worldMatrix);
	SetUniform("T_MVP", projectedMatrix);

	SetUniform("C_eyePos", renderingEngine.GetMainCamera().GetTransform().GetTransformedPos());
	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));

	DirectionalLight directionalLight = *(DirectionalLight*)renderingEngine.GetActiveLight();  // if activeLight in the renderingEngine is not a pointer, then this code doesnot work

	SetUniform("R_directionalLight.base.color", directionalLight.color);
	SetUniformf("R_directionalLight.base.intensity", directionalLight.intensity);
	SetUniform("R_directionalLight.direction", directionalLight.GetDirection());




}