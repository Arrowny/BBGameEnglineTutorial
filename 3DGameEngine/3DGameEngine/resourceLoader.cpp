#include "resourceLoader.h"

std::string LoadFile(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName.c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			std::getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "File Readin Error: unable to load file \"" << fileName << "\"" << std::endl;
	}

	return output;
}

std::string Loader::LoadShader(const std::string& fileName)
{
	return LoadShader(fileName);
}

Mesh Loader::LoadMesh(const std::string& meshFileName)
{
	std::vector<std::string> splitArray = Util::Split(meshFileName, '.');
	std::string extension = splitArray[splitArray.size() - 1];

	if (extension != "obj")
	{
		std::cerr << "Error: file extension \"" + extension + "\" is not supported " << std::endl;
		exit(1);
	}

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	std::vector<std::string> meshData = Util::Split(LoadFile(meshFileName), '\n');
	std::vector<std::string> tokens;

	for (unsigned int ii = 0; ii < meshData.size(); ii++)
	{
		tokens = Util::Split(meshData[ii], ' ');
		tokens = Util::RemoveEmptyStrings(tokens);

		if (tokens.size() == 0 || tokens[0] == "#") //empty or object file comment
		{
			continue;
		}
		else if (tokens[0] == "v") //vertex
		{
			double x = std::atof(tokens[1].c_str());
			double y = std::atof(tokens[2].c_str());
			double z = std::atof(tokens[3].c_str());
			vertices.push_back(Vertex(glm::vec3(x, y, z)));
		}
		else if (tokens[0] == "f") //face
		{
			int firstInd = (std::atoi(tokens[1].c_str()) - 1);
			int secondInd = (std::atoi(tokens[1].c_str()) - 1);
			int thirdInd = (std::atoi(tokens[1].c_str()) - 1);
			indices.push_back(firstInd); 
			indices.push_back(secondInd); 
			indices.push_back(thirdInd);
		}
	}

	Mesh output(&vertices[0], vertices.size(), &indices[0], indices.size());

	return output;
}