#pragma once
#include "shader.h"
class PhongShader :
	public Shader
{
public:
	PhongShader(const std::string& fileName);
	~PhongShader();

};

