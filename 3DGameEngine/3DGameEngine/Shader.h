#pragma once

#include <map>
#include <string>
#include <GL/glew.h>
#include <glm\glm.hpp>
#include "Timing.h"
#include "Transform.h"
#include "directionalLight.h"
#include "baseLight.h"
#include "Material.h"
#include "pointLight.h"
#include "spotLight.h"
#include "renderingEngine.h"

class Shader
{
public:
	Shader();

	Shader(const std::string& fileName);

	void Bind();
	void CompileShader();
    virtual void Update(const Transform& transform, const Material& material, renderingEngine* renderingEngine);
	static void SetPointLights(pointLight* pointLights, int arraySize);
	static void SetSpotLights(spotLight* spotLights, int arraySize);

	virtual ~Shader();
protected:
	static const unsigned int NUM_SHADERS = 3;

	enum
	{
		UNIFORM_U,
		TRANSFORM_U,
		NORMAL_U,
		LIGHTDIR_U,
		COLOR_U,
		AMBIENTL_U,
		SPECI_U,
		SPECP_U,
		EYEPOS_U,

		DIRLIGHTC_U,
		DIRLIGHTI_U,
		DIRLIGHTD_U,

		POINTLBC_U,
		POINTLBI_U,
		POINTLAC_U,
		POINTLAL_U,
		POINTLAE_U,
		POINTLP_U,
		POINTLR_U,

		SPOTLBC_U,
		SPOTLBI_U,
		SPOTLAC_U,
		SPOTLAL_U,
		SPOTLAE_U,
		SPOTLP_U,
		SPOTLR_U,
		SPOTLD_U,
		SPOTLC_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];

	static std::string LoadShader(const std::string& fileName);
	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

private:
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

};
