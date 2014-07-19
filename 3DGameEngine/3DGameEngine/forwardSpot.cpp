#include "forwardSpot.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

ForwardSpot::ForwardSpot() : 
Shader("./res/forwardSpot")
{}

void ForwardSpot::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{
	Shader::UpdateUniforms(transform, material, renderingEngine);
}

