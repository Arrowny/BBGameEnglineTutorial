#include "ForwardSpot.h"


ForwardSpot::ForwardSpot() :Shader("./res/shader/forwardSpotLight")
{
	/*fprintf(stderr, "in point shader \n");
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Porgram linking failed");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");

*/

	AddUniform("T_MVP");
	AddUniform("T_model");
	AddUniform("C_eyePos");

	AddUniform("specularIntensity");
	AddUniform("specularPower");

	AddUniform("R_spotLight.pointLight.base.color");
	AddUniform("R_spotLight.pointLight.base.intensity");
	AddUniform("R_spotLight.pointLight.atten.constant");
	AddUniform("R_spotLight.pointLight.atten.linear");
	AddUniform("R_spotLight.pointLight.atten.exponent");
	AddUniform("R_spotLight.pointLight.position");
	AddUniform("R_spotLight.pointLight.range");
	AddUniform("R_spotLight.direction");
	AddUniform("R_spotLight.cutoff");
}


ForwardSpot::~ForwardSpot()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}



void ForwardSpot::Update(Transform& transform, RenderingEngine& renderingEngine, Material& material)
{
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine.GetMainCamera().GetViewProjection()* worldMatrix;
	//glm::mat4 projectedMatrix =GetRenderingEngine()->GetMainCamera().GetViewProjection()* worldMatrix; // can not use GetRenderingEngine()->.........do not know why......
	//glm::mat4 model = projectedMatrix * worldMatrix;

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