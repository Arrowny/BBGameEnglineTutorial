#pragma once

#include "Shader.h"

class ForwardDirectional : public Shader
{
public:

	static ForwardDirectional* GetInstance()
	{
		static ForwardDirectional instance("./res/forwardDirectional");
		return &instance;
	}

	virtual void UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine);
protected:
private:
	ForwardDirectional(const std::string& fileName);

	ForwardDirectional(ForwardDirectional const&){}// Don't Implement
	void operator=(ForwardDirectional const&){} // Don't implement

};

