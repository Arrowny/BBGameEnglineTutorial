#pragma once
#include <string>
#include <GL/glew.h>
#include "Transform.h"	
#include "Camera.h"
#include "Material.h"
#include "DirectionalLight.h"

class Shader
{
public:

	Shader(const std::string& fileName);
	void Bind();//bind the shader, set the GPU in a state using vertex shader and frag shader in this class
	void Update(Transform& transform,Camera& camera, Material& material);//, DirectionalLight& directionalLight
	//void Update(float value);

	~Shader();

private:
	static const unsigned int NUM_SHADERS = 2;
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, GLenum shaderType);

	static const int MAX_POINT_LIGHTS = 4;
	static const int MAX_SPOT_LIGHTS = 4;

	enum
	{
		EYEPOS_U,
		TRANSFORM_P_U,
		TRANSFORM_U,

		FLOAT_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
	
};

