#include "objectLoader.h"
#include <iostream>
#include <map>
#include "util.h"
#include "resourceLoader.h"

void IndexedModel::calcNormals()
{
	std::vector<glm::vec3> resultNormals;
	resultNormals.reserve(positions.size());

	for (int ii = 0; ii < positions.size(); ii++)
	{
		resultNormals.push_back(glm::vec3(0.0, 0.0, 0.0));
	}

	for (int ii = 0; ii < positions.size(); ii += 3)
	{
		int i0 = indices[ii];
		int i1 = indices[ii + 1];
		int i2 = indices[ii + 2];

		glm::vec3 v1 = positions[i1] - positions[i0];
		glm::vec3 v2 = positions[i2] - positions[i0];

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		resultNormals[i0] += normal;
		resultNormals[i1] += normal;
		resultNormals[i2] += normal;
	}

	for (int ii = 0; ii < resultNormals.size(); ii++)
	{
		resultNormals[ii] = glm::normalize(resultNormals[ii]);
	}

	normals = resultNormals;
}

OBJModel::OBJModel(std::string fileName)
{
	std::vector<std::string> meshData = Util::Split(Loader::LoadFile(fileName), '\n');
	std::vector<std::string> tokens;

	for (unsigned int ii = 0; ii < meshData.size(); ii++)
	{
		tokens = Util::Split(meshData[ii], ' ');
		tokens = Util::RemoveEmptyStrings(tokens);

		if (tokens.size() > 0) //empty string
		{
			const char* lineType = tokens[0].c_str();
			switch (lineType[0])
			{
			case 'v': //vertex
			{
				double x = std::atof(tokens[1].c_str());
				double y = std::atof(tokens[2].c_str());
				double z = std::atof(tokens[3].c_str());
				positions.push_back(glm::vec3(x, y, z));
				break;
			}

			case 'vt': //texture
			{
				double u = std::atof(tokens[1].c_str());
				double v = std::atof(tokens[2].c_str());
				texCoords.push_back(glm::vec2(u, v));
				break;
			}

			case 'vn': //normal
			{
				double x = std::atof(tokens[1].c_str());
				double y = std::atof(tokens[2].c_str());
				double z = std::atof(tokens[3].c_str());
				normals.push_back(glm::vec3(x, y, z));
				break;
			}

			case 'f': //face
			{
				for (int ii = 0; ii < tokens.size() - 3; ii++) //triangulate higher degree polygons
				{
					indices.push_back(parseIndex(tokens[1]));
					indices.push_back(parseIndex(tokens[2 + ii]));
					indices.push_back(parseIndex(tokens[3 + ii]));
				}
				break;
			}

			default: break;
			}
		}
	
	}
}


OBJIndex OBJModel::parseIndex(std::string token)
{
	std::vector<std::string> values = Util::Split(token, '/');
	OBJIndex result;

	result.vertexIndex = std::atoi(values[0].c_str()) - 1;
	if (values.size() > 1)
	{
		hasTexCoords = true;
		result.uvIndex = std::atoi(values[1].c_str()) - 1;
		if (values.size() > 2)
		{
			hasNormals = true;
			result.normalIndex = std::atoi(values[3].c_str()) - 1;
		}
	}

	return result;
}

IndexedModel OBJModel::toIndexedModel()
{
	IndexedModel result;
	std::map<int, int> indexMap;

	int currentVertexIndex = 0;
	for (int ii = 0; ii < indices.size(); ii++)
	{
		OBJIndex currentIndex = indices[ii];
		

		glm::vec3 currentPosition = positions[currentIndex.vertexIndex];
		glm::vec2 currentTexCoord;
		glm::vec3 currentNormal;

		if (hasTexCoords) { currentTexCoord = texCoords[currentIndex.uvIndex]; }
		else { currentTexCoord = glm::vec2(0.0, 0.0); }
		if (hasNormals) { currentNormal = normals[currentIndex.normalIndex]; }
		else { currentNormal = glm::vec3(0.0, 0.0, 0.0); }
		
		int previousVertexIndex = -1;
		for (int jj = 0; jj < ii; jj++)
		{
			OBJIndex oldIndex = indices[jj];

			if (currentIndex == oldIndex)
			{
				previousVertexIndex = jj;
				break;
			}
		}

		if (previousVertexIndex == -1)
		{
			result.positions.push_back(currentPosition);
			result.texCoords.push_back(currentTexCoord);
			result.normals.push_back(currentNormal);
			result.indices.push_back(currentVertexIndex);
			indexMap[ii] = currentVertexIndex;
			currentVertexIndex++;
			
		}
		else
		{
			result.indices.push_back(indexMap[previousVertexIndex]);
		}
	}

	return result;
}
