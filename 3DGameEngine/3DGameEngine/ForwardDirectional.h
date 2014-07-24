#pragma once
#include "Shader.h"
#include "Lights.h"

class Shader;

class ForwardDirectional : public Shader
{
public:


	void Update(Transform& transform, RenderingEngine& renderingEngine, Material& material);

	static ForwardDirectional* GetInstance()
	{
		static ForwardDirectional Bshader;
		return &Bshader;
	}

	virtual ~ForwardDirectional();

private:
	ForwardDirectional();
	ForwardDirectional(ForwardDirectional const&) : Shader("") {}// Don't Implement
	void operator=(ForwardDirectional const&){} // Don't implement
};