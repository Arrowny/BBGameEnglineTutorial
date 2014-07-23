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

};