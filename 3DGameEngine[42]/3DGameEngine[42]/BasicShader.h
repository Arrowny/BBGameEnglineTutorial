#pragma once
#include "Shader.h"

class Shader;

class BasicShader : public Shader
{
public:
	BasicShader(const std::string& fileName);

	void Update(Transform& transform, RenderingEngine& renderingEngine, Material& material);

	static BasicShader* GetInstance()
	{
		static BasicShader Bshader("./res/btShader");
		return &Bshader;
	}

	virtual ~BasicShader();

private:
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		//EYEPOS_U,
		TRANSFORM_P_U,
		TRANSFORM_U,

		FLOAT_U,

		NUM_UNIFORMS
	};

	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};