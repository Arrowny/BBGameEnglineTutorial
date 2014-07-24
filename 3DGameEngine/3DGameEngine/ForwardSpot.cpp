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

	AddUniform("MVP");
	AddUniform("model");
	AddUniform("eyePos");

	AddUniform("specularIntensity");
	AddUniform("specularPower");

	AddUniform("spotLight.pointLight.base.color");
	AddUniform("spotLight.pointLight.base.intensity");
	AddUniform("spotLight.pointLight.atten.constant");
	AddUniform("spotLight.pointLight.atten.linear");
	AddUniform("spotLight.pointLight.atten.exponent");
	AddUniform("spotLight.pointLight.position");
	AddUniform("spotLight.pointLight.range");
	AddUniform("spotLight.direction");
	AddUniform("spotLight.cutoff");
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

	SetUniform("model", worldMatrix);
	SetUniform("MVP", projectedMatrix);
	SetUniform("eyePos", renderingEngine.GetMainCamera().GetTransform().GetTransformedPos());

	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));

	SpotLight spotLight = *(SpotLight*)renderingEngine.GetActiveLight();

	SetUniform("spotLight.pointLight.base.color", spotLight.color);
	SetUniformf("spotLight.pointLight.base.intensity", spotLight.intensity);
	SetUniformf("spotLight.pointLight.atten.constant", spotLight.atten.constant);
	SetUniformf("spotLight.pointLight.atten.linear", spotLight.atten.linear);
	SetUniformf("spotLight.pointLight.atten.exponent", spotLight.atten.exponent);
	SetUniform("spotLight.pointLight.position", spotLight.GetTransform().GetPos());
	SetUniformf("spotLight.pointLight.range", spotLight.range);
	SetUniform("spotLight.direction", spotLight.GetDirection());
	SetUniformf("spotLight.cutoff", spotLight.cutoff);

 }