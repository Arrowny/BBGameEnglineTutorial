#pragma once
#include "Shader.h"

class Shader;

class ForwardAmbient : public Shader
{
public:
	void Update(Transform& transform, RenderingEngine& renderingEngine, Material& material);

	static ForwardAmbient* GetInstance()
	{
		static ForwardAmbient Bshader;
		return &Bshader;
	}

	virtual ~ForwardAmbient();

private:
	ForwardAmbient();

	ForwardAmbient(ForwardAmbient const&) : Shader("") {}// Don't Implement
	void operator=(ForwardAmbient const&){} // Don't implement
};