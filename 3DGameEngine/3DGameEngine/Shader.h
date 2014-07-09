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

class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();
	void Update(const Transform& transform, const Camera camera, const Material& material);
	static void SetPointLights(pointLight* pointLights, int arraySize);
	static void SetSpotLights(spotLight* spotLights, int arraySize);
	void AddUniform(const std::string& uniform);

	void SetUniformi(const std::string& name, int value);
	void SetUniformf(const std::string& name, float value);
	void SetUniform(const std::string& name, const glm::fmat4& value);
	void SetUniform(const std::string& name, const glm::fvec3& value);

	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	static const unsigned int MAX_POINT_LIGHTS = 4;
	static const unsigned int MAX_SPOT_LIGHTS = 4;
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
		SPECI_U,
		SPECP_U,
		EYEPOS_U,

		POINTLBC_1,
		POINTLBI_1,
		POINTLAC_1,
		POINTLAL_1,
		POINTLAE_1,
		POINTLP_1,
		POINTLR_1,

		POINTLBC_2,
		POINTLBI_2,
		POINTLAC_2,
		POINTLAL_2,
		POINTLAE_2,
		POINTLP_2,
		POINTLR_2,

		SPOTLBC_1,
		SPOTLBI_1,
		SPOTLAC_1,
		SPOTLAL_1,
		SPOTLAE_1,
		SPOTLP_1,
		SPOTLR_1,
		SPOTLD_1,
		SPOTLC_1,

		NUM_UNIFORMS
	};

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
	std::map<std::string, int> n_uniforms;
	static directionalLight m_directionalLight;
	static pointLight* m_pointLights;
	static spotLight* m_spotLights;
	static int m_numPointLights;
	static int m_numSpotLights;

};
