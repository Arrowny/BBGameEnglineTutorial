#include "forwardDirectional.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

ForwardDirectional::ForwardDirectional() : 
Shader("./res/forwardDirectional")
{}

void ForwardDirectional::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{
	Shader::UpdateUniforms(transform, material, renderingEngine);
}
