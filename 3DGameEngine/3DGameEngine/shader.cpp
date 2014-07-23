#include "shader.h"
//#include "resourceLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

namespace
{
	std::string LoadShader(const std::string& fileName)
	{
		std::string INCLUDE_DIRECTIVE = "#include";
		//return Loader::LoadFile(fileName);
		std::ifstream file;
		file.open(fileName.c_str());

		std::string output;
		std::string line;

		if (file.is_open())
		{
			while (file.good())
			{
				std::getline(file, line);
				std::vector<std::string> tokens = Util::Split(line, ' ');

				if (tokens[0] == INCLUDE_DIRECTIVE) //must include another shader file
				{
					std::string includeName = tokens[1].substr(1, tokens[1].size() - 2);
					output.append(LoadShader(includeName));
				}
				else
				{
					output.append(line + "\n");
				}
			}
		}
		else
		{
			std::cerr << "File Readin Error: unable to load file \"" << fileName << "\"" << std::endl;
		}

		return output;
	}

	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
	{
		GLint success = 0;
		GLchar error[1024] = { 1 };

		if (isProgram)
		{
			glGetProgramiv(shader, flag, &success);
		}
		else
		{
			glGetShaderiv(shader, flag, &success);
		}

		if (success == GL_FALSE)
		{
			if (isProgram)
			{
				glGetProgramInfoLog(shader, sizeof(error), NULL, error);
			}
			else
			{
				glGetShaderInfoLog(shader, sizeof(error), NULL, error);
			}

			std::cerr << errorMessage << ": " << error << std::endl;
		}
	}

	static GLuint CreateShader(const std::string& text, GLenum shaderType)
	{
		GLuint shader = glCreateShader(shaderType);

		if (shader == 0)
		{
			std::cerr << " Error: Shader creation failed." << std::endl;
		}

		const GLchar* shaderSourceStrings[1];
		GLint ShaderSourceStringsLengths[1];

		shaderSourceStrings[0] = text.c_str();
		ShaderSourceStringsLengths[0] = text.size();

		glShaderSource(shader, 1, shaderSourceStrings, ShaderSourceStringsLengths);
		glCompileShader(shader);

		CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: shader creation failure");

		return shader;
	}
};

Shader::Shader(const std::string& fileName)
{
	shaderFileName = fileName;
	if (loadedShaders.find(fileName) != loadedShaders.end())
	{
		loadedShadersCount[fileName]++;
		m_resource = loadedShaders[fileName];
	}
	else
	{
		m_resource = new ShaderResource();
		std::string vertShaderText = LoadShader("./res/shaders/" + fileName + ".vert");
		std::string fragShaderText = LoadShader("./res/shaders/" + fileName + ".frag");

		m_resource->m_shaders[VERTEX_SHADER] = CreateShader(vertShaderText, GL_VERTEX_SHADER);
		m_resource->m_shaders[FRAGMENT_SHADER] = CreateShader(fragShaderText, GL_FRAGMENT_SHADER);

		for (unsigned int ii = 0; ii < NUM_SHADERS; ii++)
		{
			glAttachShader(m_resource->getProgram(), m_resource->m_shaders[ii]);
		}

		glLinkProgram(m_resource->getProgram());
		CheckShaderError(m_resource->getProgram(), GL_LINK_STATUS, true, "Error: Shader program linking failed");

		glValidateProgram(m_resource->getProgram());
		CheckShaderError(m_resource->getProgram(), GL_VALIDATE_STATUS, true, "Error: Shader program linking failed");

		std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> vertStructMap = findUniformStructs(vertShaderText);
		std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> fragStructMap = findUniformStructs(fragShaderText);

		addAllUniforms(vertShaderText, vertStructMap);
		addAllUniforms(fragShaderText, fragStructMap);
		loadedShaders[fileName] = m_resource;
	}
}


Shader::~Shader()
{
	if (loadedShadersCount[shaderFileName] == 0)
	{
		for (unsigned int ii = 0; ii < NUM_SHADERS; ii++)
		{
			glDetachShader(m_resource->getProgram(), m_resource->m_shaders[ii]);
			glDeleteShader(m_resource->m_shaders[ii]);
		}

		glDeleteProgram(m_resource->getProgram());
	}
	else
	{
		loadedShadersCount[shaderFileName]--;
	}

}

void Shader::Bind()
{
	glUseProgram(m_resource->getProgram());
}

void Shader::addAllUniforms(std::string shaderText, std::unordered_map<std::string, std::vector<std::pair<std::string, std::string> > > structMap)
{
	std::string UNIFORM_KEYWORD = "uniform";
	unsigned int nxtUniformLocation = shaderText.find(UNIFORM_KEYWORD);
	while (nxtUniformLocation != -1)
	{
		int begin = nxtUniformLocation + UNIFORM_KEYWORD.size() + 1;
		int end = shaderText.find(";", begin);
		std::vector<std::string> uniformLine = Util::Split(shaderText.substr(begin, end - begin), ' '); //uniformLine[0] == uniformType. uniformLine[1] == uniformName
		
		std::string uniformName = uniformLine[1]; m_resource->uniformNames.push_back(uniformName);
		std::string uniformType = uniformLine[0]; m_resource->uniformTypes.push_back(uniformType);
		
		if (structMap.find(uniformType) != structMap.end())
		{
			addUniform(structMap, uniformName, uniformType);
		}
		else
		{
			addUniform(uniformLine[1]);
		}
		
		nxtUniformLocation = shaderText.find(UNIFORM_KEYWORD, nxtUniformLocation + UNIFORM_KEYWORD.size());
	}
}

std::vector<std::string> Shader::addUniformHelper(std::unordered_map<std::string, std::vector<std::pair<std::string, std::string> > > structMap, std::string structName, std::string structType)
{
	std::vector<std::pair<std::string, std::string>> variablePairs = structMap[structType];
	std::vector<std::string> results;

	for (int ii = 0; ii < variablePairs.size(); ii++)
	{
		std::string variableName = variablePairs[ii].second;
		std::string variabletype = variablePairs[ii].first;

		if (structMap.find(variabletype) == structMap.end())
		{
			results.push_back(structName + "." + variableName);
		}
		else
		{
			std::vector<std::string> structVariables = addUniformHelper(structMap, variableName, variabletype);
			for (int jj = 0; jj < structVariables.size(); jj++)
			{
				results.push_back(structName + "." + structVariables[jj]);
			}
		}
	}

	return results;
}

void Shader::addUniform(std::unordered_map<std::string, std::vector<std::pair<std::string, std::string> > > structMap, std::string structName, std::string structType)
{
	std::vector<std::pair<std::string,std::string>> variablePairs = structMap[structType];
	for (int ii = 0; ii < variablePairs.size(); ii++)
	{
		std::string variableName = variablePairs[ii].second;
		std::string variableType = variablePairs[ii].first;

		if (structMap.find(variableType) == structMap.end())
		{
			addUniform(structName + "." + variableName);
		}
		else
		{
			std::vector<std::string> structVariables = addUniformHelper(structMap, variableName, variableType);
			for (int jj = 0; jj < structVariables.size(); jj++)
			{
				//Debug: std::cout << "adding Uniform: " << structName + "." + structVariables[jj] << std::endl;
				addUniform(structName + "." + structVariables[jj]);
			}
		}
	}
}

void Shader::addUniform(std::string uniform)
{
	GLint uniformLocation = glGetUniformLocation(m_resource->getProgram(), uniform.c_str());

	if (uniformLocation == 0xFFFFFFFF)
	{
		std::cerr << "Error: Could not find uniform " + uniform << std::endl;
		exit(1);
	}

	m_resource->m_uniforms[uniform] = uniformLocation;
}

void Shader::setUniform(std::string uniformName, GLint value)
{
	glUniform1i(m_resource->m_uniforms[uniformName], value);
}

void Shader::setUniform(std::string uniformName, GLfloat value)
{
	glUniform1f(m_resource->m_uniforms[uniformName], value);
}

void Shader::setUniform(std::string uniformName, glm::vec3 value)
{
	glUniform3f(m_resource->m_uniforms[uniformName], value.x, value.y, value.z);
}

void Shader::setUniform(std::string uniformName, glm::vec4 value)
{
	glUniform4f(m_resource->m_uniforms[uniformName], value.x, value.y, value.z, value.w);
}

void Shader::setUniform(std::string uniformName, glm::mat4 value)
{
	glUniformMatrix4fv(m_resource->m_uniforms[uniformName], 1, GL_FALSE, &value[0][0]);
}

void Shader::setUniform(std::string uniformName, Attenuation atten)
{
	setUniform(uniformName + ".constant", atten.m_constant);
	setUniform(uniformName + ".linear", atten.m_linear);
	setUniform(uniformName + ".exponent", atten.m_exponent);
}


void Shader::setUniform(std::string uniformName, DirectionalLight* dLight)
{
	setUniform(uniformName + ".base.color", dLight->m_color);
	setUniform(uniformName + ".base.intensity", dLight->m_intensity);
	setUniform(uniformName + ".direction", dLight->getDirection());
}

void Shader::setUniform(std::string uniformName, PointLight* pLight)
{
	setUniform(uniformName + ".atten", pLight->m_atten);
	setUniform(uniformName + ".base.color", pLight->m_color);
	setUniform(uniformName + ".base.intensity", pLight->m_intensity);
	setUniform(uniformName + ".position", pLight->getPosition());
	setUniform(uniformName + ".range", pLight->m_range);

}

void Shader::setUniform(std::string uniformName, SpotLight* sLight)
{
	setUniform(uniformName + ".pLight.atten", sLight->m_atten);
	setUniform(uniformName + ".pLight.base.color", sLight->m_color);
	setUniform(uniformName + ".pLight.base.intensity", sLight->m_intensity);
	glm::vec3 p = sLight->getPosition();
	setUniform(uniformName + ".pLight.position", sLight->getPosition());
	setUniform(uniformName + ".pLight.range", sLight->m_range);
	glm::vec3 d = sLight->getDirection();
	setUniform(uniformName + ".direction", sLight->getDirection());
	setUniform(uniformName + ".cutoff", sLight->m_cutoff);
}

std::unordered_map<std::string, std::vector<std::pair<std::string, std::string> > > Shader::findUniformStructs(std::string shaderText)
{
	std::string STRUCT_KEYWORD = "struct";
	unsigned int nxtStructLocation = shaderText.find(STRUCT_KEYWORD);

	std::unordered_map<std::string, std::vector<std::pair<std::string, std::string> > > structMap;
	while (nxtStructLocation != -1)
	{
		int nameBegin = nxtStructLocation + STRUCT_KEYWORD.size() + 1;
		int openBracket = shaderText.find("{", nameBegin);
		int closeBracket = shaderText.find("}", openBracket);

		std::string structName = Util::rtrim(shaderText.substr(nameBegin, openBracket - nameBegin));

		std::vector<std::pair<std::string,std::string>> structVariables;
		unsigned int nxtbracket = shaderText.find(";", openBracket);
		unsigned int beginVariable = openBracket;
		while ( (nxtbracket != -1) && (nxtbracket < closeBracket) )
		{
			std::vector<std::string> tokens = Util::Split(shaderText.substr(beginVariable, nxtbracket - beginVariable), ' ');
			std::vector<std::string> token = Util::Split(tokens[tokens.size() - 2], '\n'); //TODO: Can cause bugs. Requires that struct variables be declared a line after the bracket.
			
			std::string varName = Util::rtrim(tokens[tokens.size() - 1]);
			std::string varType = Util::ltrim(Util::ltrim(token[token.size() - 1])); 

			structVariables.push_back(std::make_pair(varType, varName));

			beginVariable = nxtbracket + 1;
			nxtbracket = shaderText.find(";", beginVariable);
		}

		structMap[structName] = structVariables;
		nxtStructLocation = shaderText.find(STRUCT_KEYWORD, nxtStructLocation + STRUCT_KEYWORD.size());
	}

	return structMap;
}

void Shader::updateUniforms(const glm::mat4& worldMatrix, Material& mat, RenderingEngine* renderingEngine)
{
	glm::mat4 MVPMatrix = renderingEngine->getCamera()->getProjectionTransform()*worldMatrix;
	for (int ii = 0; ii < m_resource->uniformNames.size(); ii++)
	{
		std::string uniformName = m_resource->uniformNames[ii];
		std::string uniformType = m_resource->uniformTypes[ii];

		std::string unprefixedName = uniformName.substr(2);
		if (Util::StartsWith(uniformName, "T_")) //taken from transform: "T_" prefix
		{
			if (uniformName == "T_MVP") { setUniform(uniformName, MVPMatrix); }
			else if (uniformName == "T_model") { setUniform(uniformName, worldMatrix); }
			else
			{
				std::cerr << "Error: unknown component of transform: " << uniformName << "." << std::endl;
				exit(1);
			}
		}
		else if (Util::StartsWith(uniformName, "R_")) //taken from rendering engine: "R_" prefix
		{
			if (uniformType == "sampler2D")
			{
				int samplerSlot = renderingEngine->getSamplerSlot(unprefixedName);
				mat.getTexture(unprefixedName)->Bind(samplerSlot);
				setUniform(uniformName, samplerSlot);
			}
			else if (uniformType == "vec3")
			{ 
				setUniform(uniformName, renderingEngine->getVector(unprefixedName));
			}
			else if (uniformType == "float")
			{
				setUniform(uniformName, renderingEngine->getFloat(unprefixedName));
			}
			else if (uniformType == "DirectionalLight")
			{
				setUniform(uniformName, (DirectionalLight*)renderingEngine->activeLight);
			}
			else if (uniformType == "PointLight")
			{
				setUniform(uniformName, (PointLight*)renderingEngine->activeLight);
			}
			else if (uniformType == "SpotLight")
			{
				setUniform(uniformName, (SpotLight*)renderingEngine->activeLight);
			}
			else
			{
				renderingEngine->setUniformStruct(worldMatrix, mat, this, uniformName, uniformType);
			}
		}
		else if (Util::StartsWith(uniformName, "C_")) //camera variable
		{
			if (unprefixedName == "eyePos")
			{
				setUniform(uniformName, renderingEngine->getCamera()->getTransform()->getTransformedTrans());
			}
			else if (uniformType == "vec3")
			{
				setUniform(uniformName, renderingEngine->getVector(unprefixedName));
			}
			else if (uniformType == "float")
			{
				setUniform(uniformName, renderingEngine->getFloat(unprefixedName));
			}
			else
			{
				std::cerr << "Error: unknown component of camera: " << uniformName << "." << std::endl;
				exit(1);
			}
		}
		else //taken from material: no prefix
		{
			if (uniformType == "vec3")
			{
				setUniform(uniformName, mat.getVector(uniformName));
			}
			else if (uniformType == "float")
			{
				setUniform(uniformName, mat.getFloat(uniformName));
			}
			else
			{
				std::cerr << "Error: unknown component of material: " << uniformName << "." << std::endl;
				exit(1);
			}
		}
	}
}