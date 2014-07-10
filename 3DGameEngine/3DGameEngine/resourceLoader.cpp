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