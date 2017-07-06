#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>



using namespace cote::graphic;

Shader::Shader()
{
}

Shader::Shader(const std::string & filename, ShaderType type)
{
	loadFromFile(filename, type);
}


Shader::~Shader()
{
	glDeleteShader(mShaderID);
}

void Shader::loadFromFile(const char * filename, ShaderType shaderType)
{
	std::fstream file;
	file.open(filename, std::ios::in);

	if (!file.good())
	{
		std::string error("Failed to open shader file");
		error += filename;
		throw(std::runtime_error(error.c_str()));
		return;
	}

	std::stringstream sstream;
	sstream << file.rdbuf();

	file.close();

	std::string str = sstream.str();

	GLint success;
	GLchar errBuffer[512];

	const GLchar * shaderText = str.c_str();
	mShaderID = glCreateShader(shaderType);
	glShaderSource(mShaderID, 1, &shaderText, NULL);
	glCompileShader(mShaderID);
	glGetShaderiv(mShaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(mShaderID, sizeof(errBuffer), NULL, errBuffer);
		std::string error("Failed to compile shader from file: ");
		error += filename;
		error += " " ;
		error += errBuffer;
		throw(GLerror(error));
		return;
	}

	mbCompiled = true;
}

void Shader::loadFromFile(const std::string & filename, ShaderType type)
{
	loadFromFile(filename.c_str(), type);
}

//GLuint Shader::createFromSource(const std::string & text, ShaderType type)
//{
//	GLint success;
//	GLchar errBuffer[512];
//
//	const GLchar * shaderText = text.c_str();
//	mShaderID = glCreateShader(type);
//	glShaderSource(mShaderID, 1, &shaderText, NULL);
//	glCompileShader(mShaderID);
//	glGetShaderiv(mShaderID, GL_COMPILE_STATUS, &success);
//
//	if (!success)
//	{
//		glGetShaderInfoLog(mShaderID, sizeof(errBuffer), NULL, errBuffer);
//		std::cerr << "Failed to compile shader from source: " << errBuffer;
//	}
//	return mShaderID;
//}