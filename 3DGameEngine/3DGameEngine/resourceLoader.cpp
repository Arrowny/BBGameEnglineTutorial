#include "resourceLoader.h"

std::string Loader::LoadFile(const std::string& fileName)
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
	return Loader::LoadFile(fileName);
}

void Loader::LoadMeshInfo(const std::string& meshFileName, std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices)
{
	std::vector<std::string> splitArray = Util::Split(meshFileName, '.');
	std::string extension = splitArray[splitArray.size() - 1];

	if (extension != "obj")
	{
		std::cerr << "Error: file extension \"" + extension + "\" is not supported " << std::endl;
		exit(1);
	}

	std::vector<std::string> meshData = Util::Split(Loader::LoadFile(meshFileName), '\n');
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
			vertices.push_back(glm::vec3(x, y, z));
		}
		else if (tokens[0] == "f") //face
		{
			//normal information etc can be stored after "/" char
			std::vector<std::string> faceInfo1 = Util::Split(tokens[1], '/');
			std::vector<std::string> faceInfo2 = Util::Split(tokens[2], '/');
			std::vector<std::string> faceInfo3 = Util::Split(tokens[3], '/');

			int firstInd = (std::atoi(faceInfo1[0].c_str()) - 1);
			int secondInd = (std::atoi(faceInfo2[0].c_str()) - 1);
			int thirdInd = (std::atoi(faceInfo3[0].c_str()) - 1);
			indices.push_back(firstInd); 
			indices.push_back(secondInd); 
			indices.push_back(thirdInd);

			if (tokens.size() > 4) //quadralaterals are being used. Create second triangle using quadralateral vertices.
			{
				faceInfo1 = Util::Split(tokens[1], '/');
				faceInfo2 = Util::Split(tokens[3], '/');
				faceInfo3 = Util::Split(tokens[4], '/');

				int firstInd = (std::atoi(faceInfo1[0].c_str()) - 1);
				int secondInd = (std::atoi(faceInfo2[0].c_str()) - 1);
				int thirdInd = (std::atoi(faceInfo3[0].c_str()) - 1);
				indices.push_back(firstInd);
				indices.push_back(secondInd);
				indices.push_back(thirdInd);

			}
		}
	}
}