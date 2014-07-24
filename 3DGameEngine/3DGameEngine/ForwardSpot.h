#pragma once
#include "Shader.h"
#include "Lights.h"

class Shader;

class ForwardSpot : public Shader
{
public:

	void Update(Transform& transform, RenderingEngine& renderingEngine, Material& material);

	static ForwardSpot* GetInstance()
	{
		static ForwardSpot Bshader;
		return &Bshader;
	}

	virtual ~ForwardSpot();

private:
	ForwardSpot();
	ForwardSpot(ForwardSpot const&) : Shader("") {}// Don't Implement
	void operator=(ForwardSpot const&){} // Don't implement
};