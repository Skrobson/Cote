#include "ShaderProgram.h"

using namespace cote::graphic;



ShaderProgram::ShaderProgram()
{
	mProgram = glCreateProgram();
}

ShaderProgram::ShaderProgram(std::initializer_list<const Shader> list)
{
	mProgram = glCreateProgram();
	for (auto& shader : list)
	{
		attachShader(shader);
	}
	linkProgram();
}

ShaderProgram::~ShaderProgram()
{
	for (auto& shader : mShaders)
	{
		glDetachShader(mProgram, shader.second);
	}
	glDeleteProgram(mProgram);
}

bool ShaderProgram::attachShader(const Shader& shader)
{
	if (!shader.isCompiled()) 
	{
		throw("Shader not compiled");
		return false;
	}
	glAttachShader(mProgram, shader.getShaderID());
	mShaders.insert(std::make_pair(shader.getType(), shader.getShaderID()));
	return true;
}

bool ShaderProgram::linkProgram()
{
	glLinkProgram(mProgram);

	GLint success;
	char errBuffer[512];
	glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(mProgram, sizeof(errBuffer), NULL, errBuffer);
		std::string error("Failed to link shader program ");
		error += errBuffer;
		throw(GLerror(error));
		return false;
	}

	mbLinked = true;

	return true;
}

void ShaderProgram::bind()const
{

	glUseProgram(mProgram);
}

void ShaderProgram::unbind()const
{
	glUseProgram(NULL);
}