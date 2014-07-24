#include "ForwardSpot.h"


ForwardSpot::ForwardSpot() :Shader("./res/shader/forwardSpotLight")
{
}


ForwardSpot::~ForwardSpot()
{

}



void ForwardSpot::Update(Transform& transform, RenderingEngine& renderingEngine, Material& material)
{
	material.GetTexture("diffuse")->Bind(0);
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine.GetMainCamera().GetViewProjection()* worldMatrix;

	SetUniform("T_model", worldMatrix);
	SetUniform("T_MVP", projectedMatrix);
	SetUniform("C_eyePos", renderingEngine.GetMainCamera().GetTransform().GetTransformedPos());

	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));

	SpotLight spotLight = *(SpotLight*)renderingEngine.GetActiveLight();

	SetUniform("R_spotLight.pointLight.base.color", spotLight.color);
	SetUniformf("R_spotLight.pointLight.base.intensity", spotLight.intensity);
	SetUniformf("R_spotLight.pointLight.atten.constant", spotLight.atten.constant);
	SetUniformf("R_spotLight.pointLight.atten.linear", spotLight.atten.linear);
	SetUniformf("R_spotLight.pointLight.atten.exponent", spotLight.atten.exponent);
	SetUniform("R_spotLight.pointLight.position", spotLight.GetTransform().GetPos());
	SetUniformf("R_spotLight.pointLight.range", spotLight.range);
	SetUniform("R_spotLight.direction", spotLight.GetDirection());
	SetUniformf("R_spotLight.cutoff", spotLight.cutoff);

 }