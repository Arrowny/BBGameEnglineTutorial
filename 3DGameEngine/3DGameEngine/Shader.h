#pragma once
#include <string>
#include <GL/glew.h>
#include "Transform.h"	
#include "Camera.h"
#include "Material.h"

class Shader
{
public:

	Shader(const std::string& fileName);
	void Bind();//bind the shader, set the GPU in a state using vertex shader and frag shader in this class
	void Update(Transform& transform,Camera& camera, Material& material);
	//void Update(float value);

	inline void SetAmbient(glm::fvec3 ambient) { ambientLight = ambient; }

	~Shader();

private:
	static const unsigned int NUM_SHADERS = 2;
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, GLenum shaderType);


	enum
	{
		TRANSFORM_U,
		BASIC_COLOR_U,
		L_AMBIENT_U,
		FLOAT_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];

	glm::vec3 ambientLight;
};

