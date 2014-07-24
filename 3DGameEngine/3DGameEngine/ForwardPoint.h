#pragma once
#include "Shader.h"
#include "Lights.h"

class Shader;

class ForwardPoint : public Shader
{
public:

	void Update(Transform& transform, RenderingEngine& renderingEngine, Material& material);

	static ForwardPoint* GetInstance()
	{
		static ForwardPoint Bshader;
		return &Bshader;
	}

	virtual ~ForwardPoint();

private:
	ForwardPoint();
	ForwardPoint(ForwardPoint const&) : Shader("") {}// Don't Implement
	void operator=(ForwardPoint const&){} // Don't implement

};