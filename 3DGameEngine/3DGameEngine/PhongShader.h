#pragma once
#include <string>
#include <GL/glew.h>
#include "Transform.h"	
#include "Camera.h"
#include "Material.h"
#include "DirectionalLight.h"

class PhongShader
{
public:

	PhongShader(const std::string& fileName);
	void Bind();//bind the shader, set the GPU in a state using vertex shader and frag shader in this class
	void Update(Transform& transform, Camera& camera, Material& material);//, DirectionalLight& directionalLight
	//void Update(float value);

	inline void SetAmbient(glm::fvec3 ambient) { ambientLight = ambient; }
	inline void SetDirectionalLight(DirectionalLight directionallight) { directionalLight = directionallight; }
	inline void SetPointLights(PointLight* pointLights, GLint numPointLights)
	{
		if (numPointLights > MAX_POINT_LIGHTS)
		{
			std::cerr << "Error: Too many point lights. Max allowed:" << MAX_POINT_LIGHTS << " is smaller than:" << numPointLights << std::endl;
		}
		else
		{
			this->numPointLights = numPointLights;
			this->pointLights = pointLights;
		}
	}
	inline void SetSpotLights(SpotLight* spotLights, GLint numSpotLights)
	{
		if (numSpotLights > MAX_SPOT_LIGHTS)
		{
			std::cerr << "Error: Too many SPOT lights. Max allowed:" << MAX_SPOT_LIGHTS << " is smaller than:" << numSpotLights << std::endl;
		}
		else
		{
			this->numSpotLights = numSpotLights;
			this->spotLights = spotLights;
		}
	}
	~PhongShader();

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
		BASIC_COLOR_U,

		L_AMBIENT_U,
		L_DIRECTIONAL_BASE_COLOR_U,
		L_DIRECTIONAL_BASE_INTENSITY_U,
		L_DIRECTIONAL_DIRECTION_U,
		L_SPECULARINTENSITY_U,
		L_SPECULARPOWER_U,

		L_POINT_BASE_COLOR_1U,
		L_POINT_BASE_INTENS_1U,
		L_POINT_ATTEN_CONS_1U,
		L_POINT_ATTEN_LINE_1U,
		L_POINT_ATTEN_EXPO_1U,
		L_POINT_POSITION_1U,
		L_POINT_RANGE_1U,

		L_POINT_BASE_COLOR_2U,
		L_POINT_BASE_INTENS_2U,
		L_POINT_ATTEN_CONS_2U,
		L_POINT_ATTEN_LINE_2U,
		L_POINT_ATTEN_EXPO_2U,
		L_POINT_POSITION_2U,
		L_POINT_RANGE_2U,

		L_SPOT_POINT_BASE_COLOR_1U,
		L_SPOT_POINT_BASE_INTENS_1U,
		L_SPOT_POINT_ATTEN_CONS_1U,
		L_SPOT_POINT_ATTEN_LINE_1U,
		L_SPOT_POINT_ATTEN_EXPO_1U,
		L_SPOT_POINT_POSITION_1U,
		L_SPOT_POINT_RANGE_1U,
		L_SPOT_DIRECTION_1U,
		L_SPOT_CUTOFF_1U,

		L_SPOT_POINT_BASE_COLOR_2U,
		L_SPOT_POINT_BASE_INTENS_2U,
		L_SPOT_POINT_ATTEN_CONS_2U,
		L_SPOT_POINT_ATTEN_LINE_2U,
		L_SPOT_POINT_ATTEN_EXPO_2U,
		L_SPOT_POINT_POSITION_2U,
		L_SPOT_POINT_RANGE_2U,
		L_SPOT_DIRECTION_2U,
		L_SPOT_CUTOFF_2U,

		FLOAT_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];

	glm::vec3 ambientLight;
	DirectionalLight directionalLight;
	//std::vector<PointLight> pointLights;
	PointLight* pointLights;
	GLint numPointLights;
	SpotLight* spotLights;
	GLint numSpotLights;

};

