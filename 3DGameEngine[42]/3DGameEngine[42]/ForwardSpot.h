#pragma once
#include "Shader.h"
#include "Lights.h"

class Shader;

class ForwardSpot : public Shader
{
public:
	ForwardSpot(const std::string& fileName);

	void Update(Transform& transform, RenderingEngine& renderingEngine, Material& material);

	static ForwardSpot* GetInstance()
	{
		static ForwardSpot Bshader("./res/shader/forwardSpotLight");
		return &Bshader;
	}



	virtual ~ForwardSpot();

private:
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		MVP,
		model,
		EYEPOS_U,

		L_SPECULARINTENSITY_U,
		L_SPECULARPOWER_U,

		L_SPOT_POINT_BASE_COLOR,
		L_SPOT_POINT_BASE_INTENS,
		L_SPOT_POINT_ATTEN_CONS,
		L_SPOT_POINT_ATTEN_LINE,
		L_SPOT_POINT_ATTEN_EXPO,
		L_SPOT_POINT_POSITION,
		L_SPOT_POINT_RANGE,
		L_SPOT_DIRECTION,
		L_SPOT_CUTOFF,

		NUM_UNIFORMS
	};

	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];

};