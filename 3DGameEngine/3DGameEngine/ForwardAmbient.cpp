#include "ForwardAmbient.h"


ForwardAmbient::ForwardAmbient() : Shader("./res/shader/forwardAmbient")
{
	//fprintf(stderr, "in ambient shader \n");
	//m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	//m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);


	//m_uniforms[MVP] = glGetUniformLocation(m_program, "T_MVP");
	//m_uniforms[ambientIntensity] = glGetUniformLocation(m_program, "R_ambientIntensity");
}


ForwardAmbient::~ForwardAmbient()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}



void ForwardAmbient::Update(Transform& transform, RenderingEngine& renderingEngine, Material& material)
{
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine.GetMainCamera().GetViewProjection()* worldMatrix;

	/*glUniformMatrix4fv(m_uniforms[MVP], 1, GL_FALSE, &projectedMatrix[0][0]);
	glUniform3fv(m_uniforms[ambientIntensity], 1, &renderingEngine.GetAmbientLight()[0]);*/

	SetUniform("T_MVP", projectedMatrix);
	SetUniform("R_ambientIntensity", renderingEngine.GetAmbientLight());

}