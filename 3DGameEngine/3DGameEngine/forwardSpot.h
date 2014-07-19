#pragma once

#include "Shader.h"

class ForwardSpot : public Shader
{
public:
	static ForwardSpot* GetInstance()
	{
		static ForwardSpot instance;
		return &instance;
	}

	virtual void UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine);
protected:
private:
	ForwardSpot();

	ForwardSpot(ForwardSpot const&) : Shader("") {}// Don't Implement
	void operator=(ForwardSpot const&){} // Don't implement
};
