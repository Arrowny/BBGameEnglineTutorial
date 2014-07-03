#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "mesh.h"
#include "util.h"
#include "vertex.h"
#include <glm\glm.hpp>

namespace Loader
{
	std::string LoadShader(const std::string& fileName);
	Mesh LoadMesh(std::string fileName);
};

