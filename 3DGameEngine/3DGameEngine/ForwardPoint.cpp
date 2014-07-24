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



	AddUniform("MVP");
	AddUniform("model");
	AddUniform("eyePos");

	AddUniform("specularIntensity");
	AddUniform("specularPower");

	AddUniform("pointLight.base.color");
	AddUniform("pointLight.base.intensity");
	AddUniform("pointLight.atten.constant");
	AddUniform("pointLight.atten.linear");
	AddUniform("pointLight.atten.exponent");
	AddUniform("pointLight.position");
	AddUniform("pointLight.range");
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

	SetUniform("model",worldMatrix);
	SetUniform("MVP", projectedMatrix);
	SetUniform("eyePos",renderingEngine.GetMainCamera().GetTransform().GetTransformedPos());
	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));

	PointLight pointLight = *(PointLight*)renderingEngine.GetActiveLight();



	SetUniform("pointLight.base.color", pointLight.color);
	SetUniformf("pointLight.base.intensity", pointLight.intensity);
	SetUniformf("pointLight.atten.constant",pointLight.atten.constant);
	SetUniformf("pointLight.atten.linear",pointLight.atten.linear);
	SetUniformf("pointLight.atten.exponent", pointLight.atten.exponent);
	SetUniform("pointLight.position", pointLight.GetTransform().GetPos());
	SetUniformf("pointLight.range", pointLight.range);



 }