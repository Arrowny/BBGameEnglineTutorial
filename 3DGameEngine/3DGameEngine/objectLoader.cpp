#include "objectLoader.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <unordered_map>
#include "util.h"
#include "resourceLoader.h"

namespace
{
	static bool CompareOBJIndexPtr(const OBJIndex* a, const OBJIndex* b)
	{
		return a->vertexIndex < b->vertexIndex;
	}

	static inline unsigned int FindNextChar(unsigned int start, const char* str, unsigned int length, char token)
	{
		unsigned int result = start;
		while (result < length)
		{
			result++;
			if (str[result] == token)
				break;
		}

		return result;
	}
}

bool OBJIndex::operator==(const OBJIndex& other)
{
	return (	(this->vertexIndex == other.vertexIndex) 
			 && (this->uvIndex == other.uvIndex) 
			 && (this->normalIndex == other.normalIndex));
}

unsigned int OBJIndex::hashCode()
{
	unsigned int BASE = 17;
	unsigned int MULTIPLIER = 31;

	int result = BASE;

	result = MULTIPLIER*result + vertexIndex;
	result = MULTIPLIER*result + uvIndex;
	result = MULTIPLIER*result + normalIndex;

	return result;
}

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
		if (tokens.size() > 0)
		{
			if ((tokens[0] == "#") || (tokens.size() == 0))
			{
				continue;
			}
			else if (tokens[0] == "v")
			{
				double x = std::atof(tokens[1].c_str());
				double y = std::atof(tokens[2].c_str());
				double z = std::atof(tokens[3].c_str());
				positions.push_back(glm::vec3(x, y, z));
			}
			else if (tokens[0] == "vt")
			{
				double u = std::atof(tokens[1].c_str());
				double v = std::atof(tokens[2].c_str());
				texCoords.push_back(glm::vec2(u, v));
			}
			else if (tokens[0] == "vn")
			{
				double x = std::atof(tokens[1].c_str());
				double y = std::atof(tokens[2].c_str());
				double z = std::atof(tokens[3].c_str());
				normals.push_back(glm::vec3(x, y, z));
			}
			else if (tokens[0] == "f")
			{
				for (int ii = 0; ii < tokens.size() - 3; ii++) //triangulate higher degree polygons
				{
					OBJIndices.push_back(parseIndex(tokens[1]));
					OBJIndices.push_back(parseIndex(tokens[2 + ii]));
					OBJIndices.push_back(parseIndex(tokens[3 + ii]));
				}
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
	IndexedModel normalModel;

	size_t numIndices = OBJIndices.size();

	std::vector<OBJIndex*> indexLookup;

	for (unsigned int i = 0; i < numIndices; i++)
		indexLookup.push_back(&OBJIndices[i]);

	std::sort(indexLookup.begin(), indexLookup.end(), CompareOBJIndexPtr);

	std::map<OBJIndex, unsigned int> normalModelIndexMap;
	std::map<unsigned int, unsigned int> indexMap;

	for (unsigned int i = 0; i < numIndices; i++)
	{
		OBJIndex* currentIndex = &OBJIndices[i];

		glm::vec3 currentPosition = positions[currentIndex->vertexIndex];
		glm::vec2 currentTexCoord;
		glm::vec3 currentNormal;

		if (hasTexCoords)
			currentTexCoord = texCoords[currentIndex->uvIndex];
		else
			currentTexCoord = glm::vec2(0, 0);

		if (hasNormals)
			currentNormal = normals[currentIndex->normalIndex];
		else
			currentNormal = glm::vec3(0, 0, 0);

		unsigned int normalModelIndex;
		unsigned int resultModelIndex;

		//Create model to properly generate normals on
		std::map<OBJIndex, unsigned int>::iterator it = normalModelIndexMap.find(*currentIndex);
		if (it == normalModelIndexMap.end())
		{
			normalModelIndex = (unsigned int)normalModel.positions.size();

			normalModelIndexMap.insert(std::pair<OBJIndex, unsigned int>(*currentIndex, normalModelIndex));
			normalModel.positions.push_back(currentPosition);
			normalModel.texCoords.push_back(currentTexCoord);
			normalModel.normals.push_back(currentNormal);
		}
		else
			normalModelIndex = it->second;

		//Create model which properly separates texture coordinates
		unsigned int previousVertexLocation = FindLastVertexIndex(indexLookup, currentIndex, result);

		if (previousVertexLocation == (unsigned int)-1)
		{
			resultModelIndex = (unsigned int)result.positions.size();

			result.positions.push_back(currentPosition);
			result.texCoords.push_back(currentTexCoord);
			result.normals.push_back(currentNormal);
		}
		else
			resultModelIndex = previousVertexLocation;

		normalModel.indices.push_back(normalModelIndex);
		result.indices.push_back(resultModelIndex);
		indexMap.insert(std::pair<unsigned int, unsigned int>(resultModelIndex, normalModelIndex));
	}

	if (!hasNormals)
	{
		normalModel.calcNormals();

		for (unsigned int i = 0; i < result.positions.size(); i++)
			result.normals[i] = normalModel.normals[indexMap[i]];
	}

	return result;
}

unsigned int OBJModel::FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result) const
{
	unsigned int start = 0;
	unsigned int end = (unsigned int)indexLookup.size();
	unsigned int current = (end - start) / 2 + start;
	unsigned int previous = start;

	while (current != previous)
	{
		OBJIndex* testIndex = indexLookup[current];

		if (testIndex->vertexIndex == currentIndex->vertexIndex)
		{
			unsigned int countStart = current;

			for (unsigned int i = 0; i < current; i++)
			{
				OBJIndex* possibleIndex = indexLookup[current - i];

				if (possibleIndex == currentIndex)
					continue;

				if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
					break;

				countStart--;
			}

			for (unsigned int i = countStart; i < indexLookup.size() - countStart; i++)
			{
				OBJIndex* possibleIndex = indexLookup[current + i];

				if (possibleIndex == currentIndex)
					continue;

				if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
					break;
				else if ((!hasTexCoords || possibleIndex->uvIndex == currentIndex->uvIndex)
					&& (!hasNormals || possibleIndex->normalIndex == currentIndex->normalIndex))
				{
					glm::vec3 currentPosition = positions[currentIndex->vertexIndex];
					glm::vec2 currentTexCoord;
					glm::vec3 currentNormal;

					if (hasTexCoords)
						currentTexCoord = texCoords[currentIndex->uvIndex];
					else
						currentTexCoord = glm::vec2(0, 0);

					if (hasNormals)
						currentNormal = normals[currentIndex->normalIndex];
					else
						currentNormal = glm::vec3(0, 0, 0);

					for (unsigned int j = 0; j < result.positions.size(); j++)
					{
						if (currentPosition == result.positions[j]
							&& ((!hasTexCoords || currentTexCoord == result.texCoords[j])
							&& (!hasNormals || currentNormal == result.normals[j])))
						{
							return j;
						}
					}
				}
			}

			return (unsigned int)-1;
		}
		else
		{
			if (testIndex->vertexIndex < currentIndex->vertexIndex)
				start = current;
			else
				end = current;
		}

		previous = current;
		current = (end - start) / 2 + start;
	}

	return (unsigned int)-1;
}

//IndexedModel OBJModel::toIndexedModel()
//{
//	IndexedModel result;
//	IndexedModel normalModel;
//	std::unordered_map<unsigned int, int> resultIndexMap; //essentially a hashmap
//	std::unordered_map<unsigned int, int> normalIndexMap; //fixes normal artifacts. Strange unexplained problem.
//	std::unordered_map<unsigned int, unsigned int> indexMap;
//
//	for (int ii = 0; ii < OBJIndices.size(); ii++)
//	{
//		OBJIndex currentIndex = OBJIndices[ii];
//		
//		glm::vec3 currentPosition = positions[currentIndex.vertexIndex];
//		glm::vec2 currentTexCoord;
//		glm::vec3 currentNormal;
//
//		if (hasTexCoords) { currentTexCoord = texCoords[currentIndex.uvIndex]; }
//		else { currentTexCoord = glm::vec2(0.0, 0.0); }
//		if (hasNormals) { currentNormal = normals[currentIndex.normalIndex]; }
//		else { currentNormal = glm::vec3(0.0, 0.0, 0.0); }
//
//		int modelVertexIndex = -1;
//		if (resultIndexMap.find(currentIndex.hashCode()) == resultIndexMap.end()) //check hasmap for currentIndex
//		{
//			modelVertexIndex = result.positions.size();
//			resultIndexMap[currentIndex.hashCode()] = result.positions.size();
//
//			result.positions.push_back(currentPosition);
//			result.texCoords.push_back(currentTexCoord);
//			result.normals.push_back(currentNormal);
//		}
//		else
//		{
//			modelVertexIndex = resultIndexMap[currentIndex.hashCode()];
//		}
//
//		int normalModelIndex = -1; 
//		if (normalIndexMap.find(currentIndex.vertexIndex) == normalIndexMap.end())
//		{
//			normalModelIndex = normalModel.positions.size();
//			normalIndexMap[currentIndex.vertexIndex] = normalModel.positions.size();
//
//			normalModel.positions.push_back(currentPosition);
//			normalModel.texCoords.push_back(currentTexCoord);
//			normalModel.normals.push_back(currentNormal);
//		}
//		else
//		{
//			normalModelIndex = modelVertexIndex = normalIndexMap[currentIndex.vertexIndex];
//		}
//		result.indices.push_back(modelVertexIndex);
//		normalModel.indices.push_back(normalModelIndex);
//		indexMap[modelVertexIndex] = normalModelIndex;
//	}
//
//	if (!hasNormals)
//	{
//		normalModel.calcNormals();
//
//		for (int ii = 0; ii < result.normals.size(); ii++)
//			result.normals[ii] = normalModel.normals[indexMap[ii]];
//	}
//	return result;
//}
