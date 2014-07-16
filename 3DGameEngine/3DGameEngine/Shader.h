
#pragma once
#include <string>
#include <GL/glew.h>
#include "Transform.h"	
#include "Camera.h"
#include "Material.h"
//#include "DirectionalLight.h"
//#include "RenderingEngine.h"

class RenderingEngine;

class Shader
{
public:
	Shader();
	void Bind();//bind the shader, set the GPU in a state using vertex shader and frag shader in this class
	virtual void Update(Transform& transform, Camera& camera, Material& material) = 0;//        , DirectionalLight& directionalLight

	virtual ~Shader();

protected:

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, GLenum shaderType);

	GLuint m_program;

	//RenderingEngine renderingEngine;

};


