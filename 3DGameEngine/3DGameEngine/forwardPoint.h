#pragma once

#include "Shader.h"

class ForwardPoint : public Shader
{
public:
	static ForwardPoint* GetInstance()
	{
		static ForwardPoint instance("./res/forwardPoint");
		return &instance;
	}

	virtual void UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine);
protected:
private:
	ForwardPoint(const std::string& fileName);

	ForwardPoint(ForwardPoint const&){}// Don't Implement
	void operator=(ForwardPoint const&){} // Don't implement
};
