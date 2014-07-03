#pragma once
#include <glm\glm.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "mesh.h"
#include "util.h"
#include "vertex.h"

class Mesh;

namespace Loader
{
	std::string LoadShader(const std::string& fileName);
	Mesh LoadMesh(const std::string& fileName);
};

