#include "shaderResource.h"


ShaderResource::ShaderResource()
{
	m_program = glCreateProgram();
}

ShaderResource::~ShaderResource()
{
	glDeleteProgram(m_program);
}

GLuint ShaderResource::getProgram()
{
	return m_program;
}
