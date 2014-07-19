#pragma once

#include "Shader.h"

class ForwardDirectional : public Shader
{
public:

	static ForwardDirectional* GetInstance()
	{
		static ForwardDirectional instance;
		return &instance;
	}

	virtual void UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine);
protected:
private:
	ForwardDirectional();

	ForwardDirectional(ForwardDirectional const&) : Shader("") {}// Don't Implement
	void operator=(ForwardDirectional const&){} // Don't implement

};

