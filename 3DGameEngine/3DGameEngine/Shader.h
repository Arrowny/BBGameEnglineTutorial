
#pragma once

//#include <GL/glew.h>
//#include "Transform.h"	
//#include "Camera.h"


#include <vector>
#include <string>
#include "Material.h"
#include "RenderingEngine.h"
#include "Transform.h"

class RenderingEngine;

class Shader
{
public:
	Shader();
	void Bind();//bind the shader, set the GPU in a state using vertex shader and frag shader in this class
	virtual void Update(Transform& transform,RenderingEngine& renderingEngine, Material& material) = 0;//        , DirectionalLight& directionalLight

	void SetRenderingEngine(RenderingEngine* renderingEngine);
	RenderingEngine* GetRenderingEngine();

	virtual ~Shader();

protected:

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, GLenum shaderType);

	GLuint m_program;

	RenderingEngine* renderingEngine;

};


