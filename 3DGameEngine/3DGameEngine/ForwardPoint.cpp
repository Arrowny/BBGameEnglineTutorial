#include "ForwardPoint.h"


ForwardPoint::ForwardPoint() : Shader("./res/shader/forwardPointLight")
{
}


ForwardPoint::~ForwardPoint()
{

}



void ForwardPoint::Update(Transform& transform, RenderingEngine& renderingEngine, Material& material)
{
	material.GetTexture("diffuse")->Bind(0);

	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine.GetMainCamera().GetViewProjection()* worldMatrix;

	SetUniform("T_model",worldMatrix);
	SetUniform("T_MVP", projectedMatrix);
	SetUniform("C_eyePos",renderingEngine.GetMainCamera().GetTransform().GetTransformedPos());
	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));

	PointLight pointLight = *(PointLight*)renderingEngine.GetActiveLight();



	SetUniform("R_pointLight.base.color", pointLight.color);
	SetUniformf("R_pointLight.base.intensity", pointLight.intensity);
	SetUniformf("R_pointLight.atten.constant",pointLight.atten.constant);
	SetUniformf("R_pointLight.atten.linear",pointLight.atten.linear);
	SetUniformf("R_pointLight.atten.exponent", pointLight.atten.exponent);
	SetUniform("R_pointLight.position", pointLight.GetTransform().GetPos());
	SetUniformf("R_pointLight.range", pointLight.range);



 }