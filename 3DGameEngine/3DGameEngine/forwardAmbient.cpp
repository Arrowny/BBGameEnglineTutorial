#include "forwardAmbient.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

ForwardAmbient::ForwardAmbient() :
Shader("./res/forwardAmbient")
{}

void ForwardAmbient::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{
	Shader::UpdateUniforms(transform, material, renderingEngine);
}