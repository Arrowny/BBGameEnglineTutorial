#pragma once
#include "Shader.h"
#include "Lights.h"

class Shader;

class ForwardPoint : public Shader
{
public:
	ForwardPoint(const std::string& fileName);

	void Update(Transform& transform, RenderingEngine& renderingEngine, Material& material);

	static ForwardPoint* GetInstance()
	{
		static ForwardPoint Bshader("./res/shader/forwardPointLight");
		return &Bshader;
	}



	virtual ~ForwardPoint();

private:
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		MVP,
		model,
		EYEPOS_U,

		L_SPECULARINTENSITY_U,
		L_SPECULARPOWER_U,

		L_POINT_BASE_COLOR,
		L_POINT_BASE_INTENS,
		L_POINT_ATTEN_CONS,
		L_POINT_ATTEN_LINE,
		L_POINT_ATTEN_EXPO,
		L_POINT_POSITION,
		L_POINT_RANGE,

		NUM_UNIFORMS
	};

	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];

};