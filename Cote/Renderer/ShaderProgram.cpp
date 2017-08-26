#include "ShaderProgram.h"

using namespace cote::graphic;



ShaderProgram::ShaderProgram()
{
	createProgram();
}

ShaderProgram::ShaderProgram(std::initializer_list<const Shader> list)
{
	createProgram();
	for (auto& shader : list)
	{
		attachShader(shader);
	}
	linkProgram();
}


bool ShaderProgram::attachShader(const Shader& shader)
{
	if (!shader.isCompiled()) 
	{
		throw("Shader not compiled");
		return false;
	}
	glAttachShader(*mProgram, shader.getShaderID());
	//mShaders.insert(std::make_pair(shader.getType(), shader.getShaderID()));
	return true;
}

bool ShaderProgram::linkProgram()
{
	glLinkProgram(*mProgram);

	GLint success;
	char errBuffer[512];
	glGetProgramiv(*mProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(*mProgram, sizeof(errBuffer), NULL, errBuffer);
		std::string error("Failed to link shader program ");
		error += errBuffer;
		throw(GLerror(error));
		return false;
	}
	for (auto& shader : this->mShaders)
	{
		glDetachShader(*mProgram, shader.second);
	}
	mShaders.clear();
	mbLinked = true;

	return true;
}

void ShaderProgram::bind()const
{

	glUseProgram(*mProgram);
}

void ShaderProgram::unbind()const
{
	glUseProgram(NULL);
}

void cote::graphic::ShaderProgram::createProgram()
{
	mProgram = std::shared_ptr<unsigned>(new unsigned(glCreateProgram()), [](unsigned* program){
		
		glDeleteProgram(*program);
		delete program;
	});
	
}
