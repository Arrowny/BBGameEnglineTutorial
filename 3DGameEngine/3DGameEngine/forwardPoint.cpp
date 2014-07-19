#include "forwardPoint.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

ForwardPoint::ForwardPoint() : 
Shader("./res/forwardPoint")
{}

void ForwardPoint::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{
	Shader::UpdateUniforms(transform, material, renderingEngine);
}