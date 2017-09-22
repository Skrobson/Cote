#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>



using namespace cote::graphic;

Shader::Shader()
{
	makeHandler();
}

Shader::Shader(const std::string & filename, ShaderType type)
{
	makeHandler();
	loadFromFile(filename, type);
}

Shader::Shader(ShaderType type, const std::string & source)
{
	makeHandler();
	createFromSource(source, type);
}

std::shared_ptr<Shader> cote::graphic::Shader::createVertexShader(const std::string & source)
{

	return std::make_shared<Shader>(ShaderType::VERTEX_SHADER,source);
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

	std::string source = sstream.str();

	createFromSource(source, shaderType);
}

void Shader::loadFromFile(const std::string & filename, ShaderType type)
{
	loadFromFile(filename.c_str(), type);
}

void cote::graphic::Shader::makeHandler()
{
	mShaderID = std::shared_ptr<unsigned>(new unsigned(), [](unsigned * handler) {
		glDeleteShader(*handler);
		delete handler;
	});
}

std::shared_ptr<Shader> cote::graphic::Shader::createFragmentShader(const std::string & source)
{
	return std::make_shared<Shader>(ShaderType::FRAGMENT_SHADER,source);
}

void Shader::createFromSource(const std::string & text, ShaderType type)
{
	GLint success;
	GLchar errBuffer[512];

	const GLchar * shaderText = text.c_str();
	*mShaderID= glCreateShader(type);
	
	glShaderSource(*mShaderID, 1, &shaderText, NULL);
	glCompileShader(*mShaderID);
	glGetShaderiv(*mShaderID, GL_COMPILE_STATUS, &success);

		if (!success)
	{
		glGetShaderInfoLog(*mShaderID, sizeof(errBuffer), NULL, errBuffer);
		std::string error("Failed to compile shader from source: ");
		error += errBuffer;
		//throw(GLerror(error));
		return ;
	}
	mbCompiled = true;
}