#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include "Util.h"
#include "physicsEngine.h"

std::unordered_map<std::string, ShaderData*> Shader::shaderResourceMap;

static void CheckShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage);
static std::vector<UniformStruct> FindUniformStructs(const std::string& shaderText);
static std::string FindUniformStructName(const std::string& structStartToOpeningBrace);
static std::vector<TypedData> FindUniformStructComponents(const std::string& openingBraceToClosingBrace);

ShaderData::ShaderData()
{
	m_program = glCreateProgram();

	if (m_program == 0)
	{
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}
}

ShaderData::ShaderData(const std::string& fileName, const unsigned int& shaderType = 0)
{
	switch (shaderType)
	{
	case Shader::BASIC_SHADER_PIPELINE:
		{
			m_program = glCreateProgram();

			if (m_program == 0)
			{
				fprintf(stderr, "Error creating shader program\n");
				exit(1);
			}

			std::string vertexShaderText = LoadShader("./res/" + fileName + ".vs");
			std::string fragmentShaderText = LoadShader("./res/" + fileName + ".fs");

			AddVertexShader(vertexShaderText);
			AddFragmentShader(fragmentShaderText);

			AddAllAttributes(vertexShaderText);

			CompileShader();

			AddShaderUniforms(vertexShaderText);
			AddShaderUniforms(fragmentShaderText);
			break;
		}
	case Shader::FULL_SHADER_PIPELINE:
		{
			m_program = glCreateProgram();

			if (m_program == 0)
			{
				fprintf(stderr, "Error creating shader program\n");
				exit(1);
			}

			std::string vertexShaderText = LoadShader("./res/" + fileName + ".vs");
			std::string	geometryShaderText = LoadShader("./res/" + fileName + ".gs");
			std::string fragmentShaderText = LoadShader("./res/" + fileName + ".fs");

			AddVertexShader(vertexShaderText);
			AddGeometryShader(geometryShaderText);
			AddFragmentShader(fragmentShaderText);

			AddAllAttributes(vertexShaderText);

			CompileShader();

			AddShaderUniforms(vertexShaderText);
			AddShaderUniforms(geometryShaderText);
			AddShaderUniforms(fragmentShaderText);
			break;
		}
	case Shader::PHYSICS_SHADER:
		{
			m_program = glCreateProgram();

			if (m_program == 0)
			{
				fprintf(stderr, "Error creating shader program\n");
				exit(1);
			}

			std::string vertexShaderText = LoadShader("./res/" + fileName + ".vs");
			std::string	geometryShaderText = LoadShader("./res/" + fileName + ".gs");
			std::string fragmentShaderText = LoadShader("./res/" + fileName + ".fs");

			AddVertexShader(vertexShaderText);
			AddGeometryShader(geometryShaderText);
			AddFragmentShader(fragmentShaderText);

			AddAllVaryings(geometryShaderText);

			AddAllAttributes(vertexShaderText);

			CompileShader();

			AddShaderUniforms(vertexShaderText);
			AddShaderUniforms(geometryShaderText);
			AddShaderUniforms(fragmentShaderText);
			break;
		}
	default:
		{
			std::cerr << "Error: attempted to load unknown shader type" << std::endl; 
			exit(1);
		}
	}
}

ShaderData::~ShaderData()
{
	for (std::vector<int>::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it)
	{
		glDetachShader(m_program, *it);
		glDeleteShader(*it);
	}
	glDeleteProgram(m_program);
}

void ShaderData::AddUniform(const std::string& uniformName, const std::string& uniformType, const std::vector<UniformStruct>& structs)
{
	bool addThis = true;

	for (unsigned int i = 0; i < structs.size(); i++)
	{
		if (structs[i].name.compare(uniformType) == 0)
		{
			addThis = false;
			for (unsigned int j = 0; j < structs[i].memberNames.size(); j++)
			{
				AddUniform(uniformName + "." + structs[i].memberNames[j].name, structs[i].memberNames[j].type, structs);
			}
		}
	}

	if (!addThis)
		return;

	unsigned int location = glGetUniformLocation(m_program, uniformName.c_str());

	assert(location != INVALID_VALUE);

	m_uniformMap.insert(std::pair<std::string, unsigned int>(uniformName, location));
}

void ShaderData::AddAllVaryings(const std::string& gsText)
{
	std::vector<const GLchar*> varyings;
	std::string vKey = "TFB_";

	size_t vLocation = gsText.find(vKey);
	while (vLocation != std::string::npos)
	{
		size_t begin = vLocation + vKey.length();
		size_t end = gsText.find(";", begin);

		std::string vName = gsText.substr(begin + 1, end - begin - 1); //TODO: may not be parsing names correctly
		varyings.push_back(vName.c_str());
		vLocation = gsText.find(vKey, end);
	}

	glTransformFeedbackVaryings(m_program, varyings.size(), &varyings[0], GL_INTERLEAVED_ATTRIBS);
}

void ShaderData::AddVertexShader(const std::string& text)
{
	AddProgram(text, GL_VERTEX_SHADER);
}

void ShaderData::AddGeometryShader(const std::string& text)
{
	AddProgram(text, GL_GEOMETRY_SHADER);
}

void ShaderData::AddFragmentShader(const std::string& text)
{
	AddProgram(text, GL_FRAGMENT_SHADER);
}

void ShaderData::AddProgram(const std::string& text, int type)
{
	int shader = glCreateShader(type);

	if (shader == 0)
	{
		fprintf(stderr, "Error creating shader type %d\n", type);
		exit(1);
	}

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar InfoLog[1024];

		glGetShaderInfoLog(shader, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", shader, InfoLog);

		exit(1);
	}

	glAttachShader(m_program, shader);
	m_shaders.push_back(shader);
}

void ShaderData::CompileShader()
{
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Invalid shader program");

}

void ShaderData::AddAllAttributes(const std::string& vertexShaderText)
{
	static const std::string ATTRIBUTE_KEY = "attribute";

	int currentAttribLocation = 0;
	size_t attributeLocation = vertexShaderText.find(ATTRIBUTE_KEY);
	while (attributeLocation != std::string::npos)
	{
		bool isCommented = false;
		size_t lastLineEnd = vertexShaderText.rfind(";", attributeLocation);

		if (lastLineEnd != std::string::npos)
		{
			std::string potentialCommentSection = vertexShaderText.substr(lastLineEnd, attributeLocation - lastLineEnd);
			isCommented = potentialCommentSection.find("//") != std::string::npos;
		}

		if (!isCommented)
		{
			size_t begin = attributeLocation + ATTRIBUTE_KEY.length();
			size_t end = vertexShaderText.find(";", begin);

			std::string attributeLine = vertexShaderText.substr(begin + 1, end - begin - 1);

			begin = attributeLine.find(" ");
			std::string attributeName = attributeLine.substr(begin + 1);

			glBindAttribLocation(m_program, currentAttribLocation, attributeName.c_str());
			currentAttribLocation++;
		}
		attributeLocation = vertexShaderText.find(ATTRIBUTE_KEY, attributeLocation + ATTRIBUTE_KEY.length());
	}
}

void ShaderData::AddShaderUniforms(const std::string& shaderText)
{
	static const std::string UNIFORM_KEY = "uniform";

	std::vector<UniformStruct> structs = FindUniformStructs(shaderText);

	size_t uniformLocation = shaderText.find(UNIFORM_KEY);
	while (uniformLocation != std::string::npos)
	{
		bool isCommented = false;
		size_t lastLineEnd = shaderText.rfind(";", uniformLocation);

		if (lastLineEnd != std::string::npos)
		{
			std::string potentialCommentSection = shaderText.substr(lastLineEnd, uniformLocation - lastLineEnd);
			isCommented = potentialCommentSection.find("//") != std::string::npos;
		}

		if (!isCommented)
		{
			size_t begin = uniformLocation + UNIFORM_KEY.length();
			size_t end = shaderText.find(";", begin);

			std::string uniformLine = shaderText.substr(begin + 1, end - begin - 1);

			begin = uniformLine.find(" ");
			std::string uniformName = uniformLine.substr(begin + 1);
			std::string uniformType = uniformLine.substr(0, begin);

			m_uniformNames.push_back(uniformName);
			m_uniformTypes.push_back(uniformType);
			AddUniform(uniformName, uniformType, structs);

		}
		uniformLocation = shaderText.find(UNIFORM_KEY, uniformLocation + UNIFORM_KEY.length());
	}
}

std::string ShaderData::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);

			if (line.find("#include") == std::string::npos)
				output.append(line + "\n");
			else
			{
				std::string includeFileName = Util::Split(line, ' ')[1];
				includeFileName = includeFileName.substr(1, includeFileName.length() - 2);

				std::string toAppend = LoadShader(includeFileName);
				output.append(toAppend + "\n");
			}
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
};

Shader::Shader(const std::string& fileName, const unsigned int& shaderType)
{
	m_fileName = fileName;

	if (shaderResourceMap.find(fileName) != shaderResourceMap.end())
	{
		shaderResourceMap[m_fileName]->AddReference();
	}
	else
	{
		shaderResourceMap[m_fileName] = new ShaderData(fileName, shaderType);
	}
}

Shader::~Shader()
{
	if (shaderResourceMap[m_fileName]->GetReferenceCount() > 0)
	{
		shaderResourceMap[m_fileName]->RemoveReference();
	}
	else
	{
		shaderResourceMap.erase(m_fileName);
	}
}


void Shader::Bind()
{
	glUseProgram(shaderResourceMap[m_fileName]->GetProgram());
}

void Shader::UpdateUniforms(PhysicsEngine* physicsEngine)
{

	for (unsigned int i = 0; i < shaderResourceMap[m_fileName]->GetUniformNames().size(); i++)
	{
		std::string uniformName = shaderResourceMap[m_fileName]->GetUniformNames()[i];
		std::string uniformType = shaderResourceMap[m_fileName]->GetUniformTypes()[i];

		if (uniformName.substr(0, 2) == "P_")
		{
			std::string unprefixedName = uniformName.substr(2, uniformName.length());

			if (uniformType == "vec3")
				SetUniformVec3(uniformName, physicsEngine->GetVector3f(unprefixedName));
			else if (uniformType == "float")
				SetUniformf(uniformName, physicsEngine->GetFloat(unprefixedName));
			else
				physicsEngine->UpdateUniformStruct(this, uniformName, uniformType);
		}
		//TODO: add physics components class. Used in updating physics shader uniforms.
		//else
		//{
		//	if (uniformType == "vec3")
		//		SetUniformVec3(uniformName, physicsComponents.GetVector3f(uniformName));
		//	else if (uniformType == "float")
		//		SetUniformf(uniformName, physicsComponents.GetFloat(uniformName));
		//	else
		//		throw uniformType + " is not supported by the physicsComponent class";
		//}
	}
}
void Shader::UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine)
{
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;

	for (unsigned int i = 0; i < shaderResourceMap[m_fileName]->GetUniformNames().size(); i++)
	{
		std::string uniformName = shaderResourceMap[m_fileName]->GetUniformNames()[i];
		std::string uniformType = shaderResourceMap[m_fileName]->GetUniformTypes()[i];

		if (uniformType == "sampler2D")
		{
			int samplerSlot = renderingEngine->GetSamplerSlot(uniformName);
			material.GetTexture(uniformName)->Bind(samplerSlot);
			SetUniformi(uniformName, samplerSlot);
		}

		else if (uniformType == "samplerCube")
		{
			int samplerSlot = renderingEngine->GetSamplerSlot(uniformName);
			material.GetTexture(uniformName)->Bind(samplerSlot);
			SetUniformi(uniformName, samplerSlot);
		}

		else if (uniformName.substr(0, 2) == "T_")
		{
			if (uniformName == "T_MVP")
				SetUniformMat4("T_MVP", projectedMatrix);
			else if (uniformName == "T_model")
				SetUniformMat4("T_model", worldMatrix);
			else
				throw "Invalid Transform Uniform: " + uniformName;
		}
		else if (uniformName.substr(0, 2) == "R_")
		{
			std::string unprefixedName = uniformName.substr(2, uniformName.length());

			if (uniformType == "vec3")
				SetUniformVec3(uniformName, renderingEngine->GetVector3f(unprefixedName));
			else if (uniformType == "float")
				SetUniformf(uniformName, renderingEngine->GetFloat(unprefixedName));
			else if (uniformType == "DirectionalLight")
				SetUniformDirectionalLight(uniformName, *(DirectionalLight*)renderingEngine->GetActiveLight());
			else if (uniformType == "PointLight")
				SetUniformPointLight(uniformName, *(PointLight*)renderingEngine->GetActiveLight());
			else if (uniformType == "SpotLight")
				SetUniformSpotLight(uniformName, *(SpotLight*)renderingEngine->GetActiveLight());
			else
				renderingEngine->UpdateUniformStruct(transform, material, this, uniformName, uniformType);
		}
		else if (uniformName.substr(0, 2) == "C_")
		{
			if (uniformName == "C_eyePos")
				SetUniformVec3(uniformName, renderingEngine->GetMainCamera().GetTransform().GetTransformedPos());
			else
				throw "Invalid Camera Uniform: " + uniformName;
		}
		else
		{
			if (uniformType == "vec3")
				SetUniformVec3(uniformName, material.GetVector3f(uniformName));
			else if (uniformType == "float")
				SetUniformf(uniformName, material.GetFloat(uniformName));
			else
				throw uniformType + " is not supported by the Material class";
		}
	}
}

void Shader::SetUniformi(const std::string& name, int value)
{
	glUniform1i(shaderResourceMap[m_fileName]->GetUniformMap().at(name), value);
}

void Shader::SetUniformf(const std::string& name, float value)
{
	glUniform1f(shaderResourceMap[m_fileName]->GetUniformMap().at(name), value);
}

void Shader::SetUniformVec3(const std::string& name, const glm::fvec3& value)
{
	glUniform3f(shaderResourceMap[m_fileName]->GetUniformMap().at(name), value.x, value.y, value.z);
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& value)
{
	glUniformMatrix4fv(shaderResourceMap[m_fileName]->GetUniformMap().at(name), 1, GL_FALSE, &(value[0][0]));
}

static void CheckShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (!success)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		fprintf(stderr, "%s: '%s'\n", errorMessage.c_str(), error);
	}
}

static std::vector<TypedData> FindUniformStructComponents(const std::string& openingBraceToClosingBrace)
{
	static const char charsToIgnore[] = { ' ', '\n', '\t', '{' };
	static const size_t UNSIGNED_NEG_ONE = (size_t)-1;

	std::vector<TypedData> result;
	std::vector<std::string> structLines = Util::Split(openingBraceToClosingBrace, ';');

	for (unsigned int i = 0; i < structLines.size(); i++)
	{
		size_t nameBegin = UNSIGNED_NEG_ONE;
		size_t nameEnd = UNSIGNED_NEG_ONE;

		for (unsigned int j = 0; j < structLines[i].length(); j++)
		{
			bool isIgnoreableCharacter = false;

			for (unsigned int k = 0; k < sizeof(charsToIgnore) / sizeof(char); k++)
			{
				if (structLines[i][j] == charsToIgnore[k])
				{
					isIgnoreableCharacter = true;
					break;
				}
			}

			if (nameBegin == UNSIGNED_NEG_ONE && isIgnoreableCharacter == false)
			{
				nameBegin = j;
			}
			else if (nameBegin != UNSIGNED_NEG_ONE && isIgnoreableCharacter)
			{
				nameEnd = j;
				break;
			}
		}

		if (nameBegin == UNSIGNED_NEG_ONE || nameEnd == UNSIGNED_NEG_ONE)
			continue;

		TypedData newData;
		newData.type = structLines[i].substr(nameBegin, nameEnd - nameBegin);
		newData.name = structLines[i].substr(nameEnd + 1);

		result.push_back(newData);
	}

	return result;
}

static std::string FindUniformStructName(const std::string& structStartToOpeningBrace)
{
	return Util::Split(Util::Split(structStartToOpeningBrace, ' ')[0], '\n')[0];
}

static std::vector<UniformStruct> FindUniformStructs(const std::string& shaderText)
{
	static const std::string STRUCT_KEY = "struct";
	std::vector<UniformStruct> result;

	size_t structLocation = shaderText.find(STRUCT_KEY);
	while (structLocation != std::string::npos)
	{
		structLocation += STRUCT_KEY.length() + 1; //Ignore the struct keyword and space

		size_t braceOpening = shaderText.find("{", structLocation);
		size_t braceClosing = shaderText.find("}", braceOpening);

		UniformStruct newStruct;
		newStruct.name = FindUniformStructName(shaderText.substr(structLocation, braceOpening - structLocation));
		newStruct.memberNames = FindUniformStructComponents(shaderText.substr(braceOpening, braceClosing - braceOpening));

		result.push_back(newStruct);
		structLocation = shaderText.find(STRUCT_KEY, structLocation);
	}

	return result;
}

void Shader::SetUniformDirectionalLight(const std::string& uniformName, const DirectionalLight& directionalLight)
{
	SetUniformVec3(uniformName + ".direction", directionalLight.GetTransform().GetTransformedForward());
	SetUniformVec3(uniformName + ".base.color", directionalLight.m_color);
	SetUniformf(uniformName + ".base.intensity", directionalLight.m_intensity);
}

void Shader::SetUniformPointLight(const std::string& uniformName, const PointLight& pointLight)
{
	SetUniformVec3(uniformName + ".base.color", pointLight.m_color);
	SetUniformf(uniformName + ".base.intensity", pointLight.m_intensity);
	SetUniformf(uniformName + ".atten.constant", pointLight.atten.m_constant);
	SetUniformf(uniformName + ".atten.linear", pointLight.atten.m_linear);
	SetUniformf(uniformName + ".atten.exponent", pointLight.atten.m_exponent);
	SetUniformVec3(uniformName + ".position", pointLight.GetTransform().GetTransformedPos());
	SetUniformf(uniformName + ".range", pointLight.range);
}

void Shader::SetUniformSpotLight(const std::string& uniformName, const SpotLight& spotLight)
{
	SetUniformVec3(uniformName + ".pointLight.base.color", spotLight.m_color);
	SetUniformf(uniformName + ".pointLight.base.intensity", spotLight.m_intensity);
	SetUniformf(uniformName + ".pointLight.atten.constant", spotLight.atten.m_constant);
	SetUniformf(uniformName + ".pointLight.atten.linear", spotLight.atten.m_linear);
	SetUniformf(uniformName + ".pointLight.atten.exponent", spotLight.atten.m_exponent);
	SetUniformVec3(uniformName + ".pointLight.position", spotLight.GetTransform().GetTransformedPos());
	SetUniformf(uniformName + ".pointLight.range", spotLight.range);
	SetUniformVec3(uniformName + ".direction", spotLight.GetTransform().GetTransformedForward());
	SetUniformf(uniformName + ".cutoff", spotLight.cutoff);
}