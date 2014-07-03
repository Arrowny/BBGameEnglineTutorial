#pragma once
#include <glm\glm.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"
#include "vertex.h"

namespace Loader
{
	std::string LoadFile(const std::string& fileName);
	std::string LoadShader(const std::string& fileName);
	void LoadMeshInfo(const std::string& meshFileName, std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices);
};

