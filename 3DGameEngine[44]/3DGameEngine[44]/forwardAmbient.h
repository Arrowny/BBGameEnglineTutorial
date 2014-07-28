#pragma once

#include "Shader.h"

class ForwardAmbient : public Shader
{
public:

	static ForwardAmbient* GetInstance()
	{
		static ForwardAmbient instance("./res/forwardAmbient");
		return &instance;
	}

	virtual void UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine);
protected:
private:
	ForwardAmbient(const std::string& fileName);

	ForwardAmbient(ForwardAmbient const&){}// Don't Implement
	void operator=(ForwardAmbient const&){} // Don't implement

};
