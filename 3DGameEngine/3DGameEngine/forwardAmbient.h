#pragma once

#include "Shader.h"

class ForwardAmbient : public Shader
{
public:
	static ForwardAmbient* GetInstance()
	{
		static ForwardAmbient instance;
		return &instance;
	}

	virtual void UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine);
protected:
private:
	ForwardAmbient();

	ForwardAmbient(ForwardAmbient const&) : Shader("") {}// Don't Implement
	void operator=(ForwardAmbient const&){} // Don't implement
};
