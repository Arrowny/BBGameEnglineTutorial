#include "ForwardPoint.h"


ForwardPoint::ForwardPoint() : Shader("./res/shader/forwardPointLight")
{
	//fprintf(stderr, "in point shader \n");
	//m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	//m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	//for (unsigned int i = 0; i < NUM_SHADERS; i++)
	//	glAttachShader(m_program, m_shaders[i]);

	//glLinkProgram(m_program);
	//CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Porgram linking failed");

	//glValidateProgram(m_program);
	//CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");



	AddUniform("T_MVP");
	AddUniform("T_model");
	AddUniform("C_eyePos");

	AddUniform("specularIntensity");
	AddUniform("specularPower");

	AddUniform("R_pointLight.base.color");
	AddUniform("R_pointLight.base.intensity");
	AddUniform("R_pointLight.atten.constant");
	AddUniform("R_pointLight.atten.linear");
	AddUniform("R_pointLight.atten.exponent");
	AddUniform("R_pointLight.position");
	AddUniform("R_pointLight.range");
}


ForwardPoint::~ForwardPoint()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}



void ForwardPoint::Update(Transform& transform, RenderingEngine& renderingEngine, Material& material)
{
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine.GetMainCamera().GetViewProjection()* worldMatrix;
	//glm::mat4 projectedMatrix =GetRenderingEngine()->GetMainCamera().GetViewProjection()* worldMatrix; // can not use GetRenderingEngine()->.........do not know why......
	//glm::mat4 model = projectedMatrix * worldMatrix;

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