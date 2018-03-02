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

/**
* @throws GlException
*/
Shader::Shader(ShaderType type, const std::string & source)
{
	makeHandler();
	createFromSource(source, type);
}

std::shared_ptr<Shader> cote::graphic::Shader::createVertexShader(const std::string & source)
{

	return std::make_shared<Shader>(ShaderType::VERTEX_SHADER,source);
}



/**
 * @throws std::exception
 * @throws GlException
 */
void Shader::loadFromFile(const char * filename, ShaderType shaderType)
{
	std::fstream file;
	file.open(filename, std::ios::in);

	if (!file.good())
	{
		std::string error("Failed to open shader file");
		error += filename;
		throw(std::exception(error.c_str()));
	}

	std::stringstream sstream;
	sstream << file.rdbuf();

	file.close();

	std::string source = sstream.str();

	createFromSource(source, shaderType);
}

/**
* @throws GlException
* @throws std::exception
*/
void Shader::loadFromFile(const std::string & filename, ShaderType type)
{
	loadFromFile(filename.c_str(), type);
}

void cote::graphic::Shader::makeHandler()
{
	shaderID = std::shared_ptr<unsigned>(new unsigned(), [](unsigned * handler) {
		glDeleteShader(*handler);
		delete handler;
	});
}

std::shared_ptr<Shader> cote::graphic::Shader::createFragmentShader(const std::string & source)
{
	return std::make_shared<Shader>(ShaderType::FRAGMENT_SHADER,source);
}

/**
 * @throws GlException
 */
void Shader::createFromSource(const std::string & text, ShaderType type)
{
	GLint success;
	GLchar errBuffer[512];

	const GLchar * shaderText = text.c_str();
	*shaderID= glCreateShader(type);
	
	glShaderSource(*shaderID, 1, &shaderText, NULL);
	glCompileShader(*shaderID);
	glGetShaderiv(*shaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(*shaderID, sizeof(errBuffer), NULL, errBuffer);
		std::string error("Failed to compile shader from source: ");
		error += errBuffer;
		throw(GlException(error));
	}
	compiled = true;
}