#pragma once
#include "Shader.h"
#include "Lights.h"

class Shader;

class ForwardDirectional : public Shader
{
public:
	ForwardDirectional(const std::string& fileName);

	void Update(Transform& transform, RenderingEngine& renderingEngine, Material& material);

	static ForwardDirectional* GetInstance()
	{
		static ForwardDirectional Bshader("./res/shader/fowardDirectional");
		return &Bshader;
	}

	

	virtual ~ForwardDirectional();

private:
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		MVP,
		model,
		EYEPOS_U,
		L_SPECULARINTENSITY_U,
		L_SPECULARPOWER_U,

		L_DIRECTIONAL_BASE_COLOR_U,
		L_DIRECTIONAL_BASE_INTENSITY_U,
		L_DIRECTIONAL_DIRECTION_U,


		NUM_UNIFORMS
	};

	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];

};