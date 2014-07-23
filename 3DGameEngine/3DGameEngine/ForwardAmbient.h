#pragma once
#include "Shader.h"

class Shader;

class ForwardAmbient : public Shader
{
public:
	ForwardAmbient(const std::string& fileName);

	void Update(Transform& transform, RenderingEngine& renderingEngine, Material& material);

	static ForwardAmbient* GetInstance()
	{
		static ForwardAmbient Bshader("./res/shader/forwardAmbient");
		return &Bshader;
	}

	virtual ~ForwardAmbient();

private:
	//static const unsigned int NUM_SHADERS = 2;

	//enum
	//{
	//	MVP,
	//	ambientIntensity,

	//	NUM_UNIFORMS
	//};

	//GLuint m_shaders[NUM_SHADERS];
	//GLuint m_uniforms[NUM_UNIFORMS];
};