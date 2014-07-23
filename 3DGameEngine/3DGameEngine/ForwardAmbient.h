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

};