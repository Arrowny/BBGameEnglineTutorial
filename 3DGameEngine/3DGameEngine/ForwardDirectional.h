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


};