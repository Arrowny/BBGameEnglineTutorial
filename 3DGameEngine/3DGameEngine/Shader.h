#pragma once

#include <string>
#include <GL/glew.h>
#include <glm\glm.hpp>
#include "Timing.h"
#include "Transform.h"
#include "directionalLight.h"
#include "baseLight.h"
#include "Material.h"

class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();
	void Update(const Transform& transform, const Camera camera, glm::fvec4 color);

	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	enum
	{
		UNIFORM_U,
		TRANSFORM_U,
		NORMAL_U,
		LIGHTDIR_U,
		COLOR_U,
		AMBIENTL_U,
		DIRLIGHTC_U,
		DIRLIGHTI_U,
		DIRLIGHTD_U,

		NUM_UNIFORMS
	};

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
	static directionalLight m_directionalLight;

};
